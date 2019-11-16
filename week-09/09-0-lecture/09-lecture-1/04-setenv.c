// simple example of setting an environment variable 

#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>

int main(void) {
    setenv("STATUS", "great", 1);
    char *getenv_argv[] = {"./getenv", NULL};
    pid_t pid;
    extern char **environ;
    if (posix_spawn(&pid, "./getenv", NULL, NULL, getenv_argv, environ) != 0) {
        perror("spawn");
        exit(1);
    }
    return 0;
}