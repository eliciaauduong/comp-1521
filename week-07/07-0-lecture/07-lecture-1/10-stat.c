// call stat on each command line argument as simple example of its use 

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void stat_file(char *pathname);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        stat_file(argv[arg]);
    }
    return 0;
}

void stat_file(char *pathname) {
    struct stat s;

    printf("stat(\"%s\", &s)\n", pathname);

    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }

    printf(" s.st_ino =   %10ld  # Inode number\n", s.st_ino);
    printf(" s.st_mode =  %10o  # File mode \n", s.st_mode);
    printf(" s.st_nlink = %10ld  # Link count \n", (long)s.st_nlink);
    printf(" s.st_uid =   %10u  # Owner uid\n", s.st_uid);
    printf(" s.st_gid =   %10u  # Group gid\n", s.st_gid);
    printf(" s.st_size =  %10ld  # File size (bytes)\n", (long)s.st_size);

    printf(" s.st_mtime = %10ld  # Modification time (seconds since 01/01/70)\n", (long)s.st_mtime);
}