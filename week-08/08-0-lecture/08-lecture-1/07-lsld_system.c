// spawn ls -ld adding as argument the arguments we have been given 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *ls = "/bin/ls -ld";
    int command_length = strlen(ls);
    for (int i = 1; i < argc; i++) {
        command_length += strlen(argv[i]) + 1;
    }

    // create command as string
    char command[command_length + 1];
    strcpy(command, ls);
    for (int i = 1; i < argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }

    int exit_status = system(command);
    return exit_status;
}