#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cowrie.h"
#include "subset2.h"

#define MAX_LINE_CHARS 1024

// save every command executed
void appendHistory(char **command, char *pathname) {
    // open file to append
    FILE *f = fopen(pathname, "a");
    
    // add each argument to $HOME./diary
    for (int i = 0; command[i] != NULL; ++i) {
        fprintf(f, "%s ", command[i]);    
    }
    
    // add newline
    fprintf(f, "\n"); 
    
    // close file
    fclose(f);
}

// count the number of lines in $HOME/.cowrie_history
int lineCount(char *pathname) {
    // open file to read
    FILE *f = fopen(pathname, "r");
    
    int line = 0;
    char comm[MAX_LINE_CHARS];
    while (fgets(comm, MAX_LINE_CHARS, f) != NULL) {
        line++;
    }
    
    line--;
    return line;    
}

// add a built-in command history n which prints the last n commands
// if n is not specified it should default to 10
void history(int last, char *pathname) {
    // open file to read
    FILE *f = fopen(pathname, "r");
    int size = lineCount(pathname);
    int i = 0;
    
    char comm[MAX_LINE_CHARS];
    while (fgets(comm, MAX_LINE_CHARS, f) != NULL && i < size) {
        if (i >= (size - last) && i < size) {
            printf("%d: %s", i, comm);
        }
        i++;
    }
    
    fclose(f);
    return;
}

void printExe(int command, char *pathname, char **path, char **environ) {
    
    FILE *f = fopen(pathname, "r");
    int size = lineCount(pathname);
    char comm[MAX_LINE_CHARS];
    int i = 0;
    while (fgets(comm, MAX_LINE_CHARS, f) != NULL && i <= size) {
        if (i == command) {
            printf("%s", comm);
            char **args = tokenize(comm, WORD_SEPARATORS, SPECIAL_CHARS);
            execute_command(args, path, environ);
            free_tokens(args);
        }
        i++;
    }
    return;
}
