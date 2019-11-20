#include "subset2.h"

// save every command executed
void appendHistory(char **command) {
    // from COMP1521 - week 09 lab
    
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