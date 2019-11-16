// simple example using a pipe with posix_spawn to capture output from spawned process 

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

    // tell spawned process to close unused read end of pipe
    // without this - spawned process would not receive EOF
    // when read end of the pipe is closed below,
    if (posix_spawn_file_actions_addclose(&actions, pipe_file_descriptors[0]) != 0) {
        perror("posix_spawn_file_actions_init");
        return 1;
    }

    // tell spawned process to replace file descriptor 1 (stdout)
    // with write end of the pipe
    if (posix_spawn_file_actions_adddup2(&actions, pipe_file_descriptors[1], 1) != 0) {
        perror("posix_spawn_file_actions_adddup2");
        return 1;
    }

    pid_t pid;
    extern char **environ;
    char *date_argv[] = {"/bin/date", "--utc", NULL};
    if (posix_spawn(&pid, "/bin/date", &actions, NULL, date_argv, environ) != 0) {
        perror("spawn");
        return 1;
    }

    // close unused write end of pipe
    // in some case processes will deadlock without this
    // not in this case, but still good practice
    close(pipe_file_descriptors[1]);

    // creae a stdio stream from read end of pipe
    FILE *f = fdopen(pipe_file_descriptors[0], "r");
    if (f == NULL) {
        perror("fdopen");
        return 1;
    }

    // read a line from read-end of pipe
    char line[256];
    if (fgets(line, sizeof line, f) == NULL) {
        fprintf(stderr, "no output from date\n");
        return 1;
    }

    printf("output captured from /bin/date was: '%s'\n", line);

    // close read-end of the pipe
    // spawned process will now receive EOF if attempts to read input
    fclose(f);

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    printf("/bin/date exit status was %d\n", exit_status);

    return 0;
}