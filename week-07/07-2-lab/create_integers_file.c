////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  create_integers_file.c                                                    //
//  -----                                                                     //
//  Write a C program, create_integers_file, which takes 3 arguments:         //
//      1. a filename,                                                        //
//      2. the beginning of a range of integers, and                          //
//      3. the end of a range of integers;                                    //
//  and which creates a file of this name containing the specified integers.  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    
    char *fname = argv[1]; // get the filename
    int start = atoi(argv[2]); // the beginning of a range of integers
    int end = atoi(argv[3]); // the end of a range of integers
    
    FILE *f = fopen(fname, "w"); // open the file to write to
    for (int i = start; i <= end; i++) { // print each number in range to file
        fprintf(f, "%d\n", i);
    }
    fclose(f); // close the file
    return 0;
}