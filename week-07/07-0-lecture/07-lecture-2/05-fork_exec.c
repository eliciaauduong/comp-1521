// simple example of classic fork/exec run date --utc to print current UTC 
// use posix_spawn instead 

#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid == -1) {
        // the fork failed, perror will print why
        perror("fork");
    } else if (pid == 0) {
        // child

        char *date_argv[] = {"/bin/date", "--utc", NULL};

        execvp("/bin/date", date_argv);

        // execution will not reach here if exec is successful
        perror("execvpe");
        return 1;
    } else {
        // parent

        int exit_status;
        if (waitpid(pid, &exit_status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        printf("/bin/date exit status was %d\n", exit_status);
    }

    return 0;
}