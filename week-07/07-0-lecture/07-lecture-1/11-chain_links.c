// silly program which attempts to creates a long chain of symbolic links 

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>


int main(int argc, char *argv[]) {
    char pathname[256] = "hello.txt";

    // create target file
    FILE *f1;
    if ((f1 = fopen(pathname, "w")) == NULL) {
        perror(pathname);
        return 1;
    }
    fprintf(f1, "Hello Andrew!\n");
    fclose(f1);

    for (int i = 0; i < 1000;i++) {
        printf("Verifying '%s' contains: ", pathname);
        FILE *f2;
        if ((f2 = fopen(pathname, "r")) == NULL) {
            perror(pathname);
            return 1;
        }
        int c;
        while ((c = fgetc(f2)) != EOF) {
            fputc(c, stdout);
        }
        fclose(f2);

        char new_pathname[256];
        snprintf(new_pathname, sizeof new_pathname, "hello_%d.txt", i);

        printf("Creating a symbolic link %s -> %s\n", new_pathname, pathname);
        if (symlink(pathname, new_pathname) != 0) {
            perror(pathname);
            return 1;
        }

        strcpy(pathname, new_pathname);

    }

    return 0;
}