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
// add a built-in command history n which prints the last n commands
// if n is not specified it should default to 10
void history(int last, char *pathname) {
    // open file to read
    FILE *f = fopen(pathname, "r");
    int size = lineCount(pathname);
    int i = 0;
    
    char comm[MAX_LINE_CHARS];
    while (fgets(comm, MAX_LINE_CHARS, f) != NULL && i < size) {
        if (i >= (size - last)) {
            printf("%d: %s", i, comm);
        }
        i++;
    }
    
    fclose(f);
}

// count the number of lines in $HOME/.cowrie_history
static int lineCount(char *pathname) {
    // open file to read
    FILE *f = fopen(pathname, "r");
    
    int line = 0;
    char comm[MAX_LINE_CHARS];
    while (fgets(comm, MAX_LINE_CHARS, f) != NULL) {
        line++;
    }
    
    return line;    
}