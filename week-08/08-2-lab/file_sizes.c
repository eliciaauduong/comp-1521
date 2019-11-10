////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  file_sizes.c                                                              //
//  -----                                                                     //
//  Write a C program, file_sizes.c, which is given one or more filenames as  //
//  command line arguments. It should print one line for each filename which  //
//  gives the size in bytes of the file. It should also print a line giving   //
//  the combined number of bytes in the files.                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

long int calcSize(char *fname);

int main(int argc, char *argv[]) {

    int i = 1;
    long int total = 0;    
    while (i < argc) {
        printf("%s: %ld bytes\n", argv[i], calcSize(argv[i])); // each file size
        total += calcSize(argv[i]);
        i++;
    }
    
    printf("Total: %ld bytes\n", total); // total file size
    return 0;
}

long int calcSize(char *fname) {
    struct stat s; // get the stats for a file
    if (stat(fname, &s) != 0) {
        perror(fname);
        exit(1);
    }
    
    return s.st_size; // return the size of a file
}