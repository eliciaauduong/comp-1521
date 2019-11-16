#include <stdio.h>
#include <unistd.h>

int main(void) {

    // fork creates 2 identical copies of program
    // only return value is different

    pid_t pid = fork();

    if (pid == -1) {
        // the fork failed, perror will print why
        perror("fork");
    } else if (pid == 0) {
        printf("I know I am the child because fork() returned %d.\n", pid);
    } else {
        printf("I know I am the parent because fork() returned %d.\n", pid);
    }

    return 0;
}