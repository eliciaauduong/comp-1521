// use repeated chdir("..") to climb to the root of the file system as a silly example of getcwd and chdir 

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define PATH_MAX 100000 // idk

int main(void) {
    char pathname[PATH_MAX];
    while (1) {
        if (getcwd(pathname, sizeof pathname) == NULL) {
            perror("getcwd");
            return 1;
        }
        printf("getcwd() returned %s\n", pathname);

        if (strcmp(pathname, "/") == 0) {
            return 0;
        }

        if (chdir("..") != 0) {
            perror("chdir");
            return 1;
        }
    }
    return 0;
}