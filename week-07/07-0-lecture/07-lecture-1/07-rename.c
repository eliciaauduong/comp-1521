// rename the specified file 

#include <stdio.h>

/*
$ dcc rename.c
$ ./a.out rename.c renamed.c
$ ls -l  renamed.c
renamed.c
$
*/

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <old-filename> <new-filename>\n", argv[0]);
        return 1;
    }

    if (rename(argv[1], argv[2]) != 0) {
        fprintf(stderr, "%s rename <old-filename> <new-filename> failed:", argv[0]);
        perror("");
        return 1;
    }

    return 0;
}