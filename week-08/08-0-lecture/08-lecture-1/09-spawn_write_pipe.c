// simple example of using a pipe to with posix_spawn to sending input 
// to spawned process
 
#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

int main(void) {
    // create a pipe
    int pipe_file_descriptors[2];
    if (pipe(pipe_file_descriptors) == -1) {
        perror("pipe");
        return 1;
    }

    // create a list of file actions to be carried out on spawned process
    posix_spawn_file_actions_t actions;
    if (posix_spawn_file_actions_init(&actions) != 0) {
        perror("posix_spawn_file_actions_init");
        return 1;
    }

    // tell spawned process to close unused write end of pipe
    // without this - spawned process will not receive EOF
    // when write end of the pipe is closed below,
    // because spawned process also has the write-end open
    // deadlock will result
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[1]) != 0) {
        perror("posix_spawn_file_actions_init");
        return 1;
    }

    // tell spawned process to replace file descriptor 0 (stdin)
    // with read end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[0], 0) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        return 1;
    }


    // create a process running /usr/bin/sort
    // sort reads lines from stdin and prints them in sorted order
    char *sort_argv[] = {"sort", NULL};
    pid_t pid;
    extern char **environ;
    if (posix_spawn(&pid, "/usr/bin/sort", &actions, NULL, sort_argv, environ) != 0) {
        perror("spawn");
        return 1;
    }

    // close unused read end of pipe
    close(pipe_file_descriptors[0]);

    // create a stdio stream from write-end of pipe
    FILE *f = fdopen(pipe_file_descriptors[1], "w");
    if (f == NULL) {
        perror("fdopen");
        return 1;
    }

    // send some input to the /usr/bin/sort process
    //sort with will print the lines to stdout in sorted order
    fprintf(f, "sort\nwords\nplease\nthese\n");

    // close write-end of the pipe
    // without this sort will hang waiting for more input
    fclose(f);

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    printf("/usr/bin/sort exit status was %d\n", exit_status);

    return 0;
}