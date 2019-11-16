// spawn ls -ld adding as argument the arguments we have been given 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
// #include <spawn.h>
// #include <sys/wait.h>

int main(int argc, char *argv[]) {

    char *ls_argv[argc + 2];
    ls_argv[0] = "/bin/ls";
    ls_argv[1] = "-ld";
    for (int i = 1; i <= argc; i++) {
        ls_argv[i + 1] = argv[i];
    }

    pid_t pid;
    extern char **environ;
    if (posix_spawn(&pid, "/bin/ls", NULL, NULL, ls_argv, environ) != 0) {
        perror("spawn");
        exit(1);
    }

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        exit(1);
    }

    // exit with whatever status ls exited with
    return exit_status;
}