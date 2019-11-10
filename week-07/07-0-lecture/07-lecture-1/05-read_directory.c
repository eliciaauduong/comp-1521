// list the contenst of directories specified as command-line arguments 

#include <stdio.h>
#include <dirent.h>

/*
$ dcc read_directory.c
$ ./a.out .
read_directory.c
a.out
.
..
$
*/

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        DIR *dirp = opendir(argv[arg]);
        if (dirp == NULL) {
            perror(argv[arg]);  // prints why the open failed
            return 1;
        }

        struct dirent *de;

        while ((de = readdir(dirp)) != NULL) {
            printf("%ld %s\n", de->d_ino, de->d_name);
        }

        closedir(dirp);
    }
    return 0;
}