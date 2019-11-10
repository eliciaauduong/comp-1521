////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  file_modes.c                                                              //
//  -----                                                                     //
//  Write a C program, file_modes.c, which is given one or more pathnames as  //
//  command line arguments. It should print one line for each pathnames which //
//  gives the permissions of the file or directory.                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void getPerm(char *fname);

int main(int argc, char *argv[]) {

    int i = 1;
    while (i < argc) { // for every file
        getPerm(argv[i]); // print permissions
        printf(" %s\n", argv[i]); // print filename
        i++;
    }
    
    return 0;
}

void getPerm(char *fname) {

    struct stat s; // get stats for each file
    if (stat(fname, &s) != 0) {
        perror(fname);
        exit(1);
    }
    
    mode_t m = s.st_mode; // get the mode for each file

    // print '-' if regular file and 'd' if directory
    if (S_ISREG(m)) { 
        printf("-");
    } else if (S_ISDIR(m)) {
        printf("d");
    }
    
    char perm = 0; // variable to store permissions
    
    // user permissions
    perm = (m & S_IRUSR) ? 'r' : '-'; // check read permission for user
    printf("%c", perm);
    
    perm = (m & S_IWUSR) ? 'w' : '-'; // check write permission for user
    printf("%c", perm);
    
    perm = (m & S_IXUSR) ? 'x' : '-'; // check execute permission for user
    printf("%c", perm);

    // group permissions
    perm = (m & S_IRGRP) ? 'r' : '-'; // check read permission for group
    printf("%c", perm);
    
    perm = (m & S_IWGRP) ? 'w' : '-'; // check write permission for group
    printf("%c", perm);
    
    perm = (m & S_IXGRP) ? 'x' : '-'; // check execute permission for group
    printf("%c", perm);
    
    // other permissions
    perm = (m & S_IROTH) ? 'r' : '-'; // check read permission for other
    printf("%c", perm);
    
    perm = (m & S_IWOTH) ? 'w' : '-'; // check write permission for other
    printf("%c", perm);
    
    perm = (m & S_IXOTH) ? 'x' : '-'; // check execute permission for other
    printf("%c", perm);
    
}