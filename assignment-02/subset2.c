#include "subset2.h"

#define MAX_LINE_CHARS 1024

// save every command executed
void appendHistory(char **command) {
    // from COMP1521 - week 09 lab
    
    // get HOME value
    char *homeEnv = getenv("HOME");
    if (homeEnv == NULL) {
        perror("HOME");
        return;
    }
    
    // set value of /.cowrie_history
    char *history = ".cowrie_history";
    
    // construct complete pathname $HOME/.cowrie_history
    int len = strlen(homeEnv) + strlen(history) + 2;
    char pathname[len];
    snprintf(pathname, len, "%s/%s", homeEnv, history);

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
void history(int last) {
    // get HOME value
    char *homeEnv = getenv("HOME");
    if (homeEnv == NULL) {
        perror("HOME");
        return;
    }
    
    // set value of /.diary
    char *history = ".cowrie_history";
    
    // construct complete pathname $HOME/.cowrie_history
    int len = strlen(homeEnv) + strlen(history) + 2;
    char pathname[len];
    snprintf(pathname, len, "%s/%s", homeEnv, history);

    // open file to append
    FILE *f = fopen(pathname, "r");
    
    int size = lineCount();

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
static int lineCount(void) {
    // get HOME value
    char *homeEnv = getenv("HOME");
    if (homeEnv == NULL) {
        perror("HOME");
        return -1;
    }
    
    // set value of /.diary
    char *history = ".cowrie_history";
    
    // construct complete pathname $HOME/.cowrie_history
    int len = strlen(homeEnv) + strlen(history) + 2;
    char pathname[len];
    snprintf(pathname, len, "%s/%s", homeEnv, history);

    // open file to append
    FILE *f = fopen(pathname, "r");
    
    int line = 0;
    char comm[MAX_LINE_CHARS];
    while (fgets(comm, MAX_LINE_CHARS, f) != NULL) {
        line++;
    }
    
    return line;    
}