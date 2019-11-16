// simple example of program replacing itself with exec 

#include <stdio.h>
#include <unistd.h>

int main(void) {

    char *echo_argv[] = {"/bin/echo", "good-bye", "cruel", "world", NULL};
    execv("/bin/echo", echo_argv);

    // if we get here there has been an error
    perror("");
    return 1;
}