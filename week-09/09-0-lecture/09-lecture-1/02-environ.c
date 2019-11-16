// print all environment variables
 
#include <stdio.h>

int main(void) {
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}