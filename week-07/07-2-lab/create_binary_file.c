////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  create_binary_file.c                                                      //
//  -----                                                                     //
//  Write a C program, create_binary_file, which takes at least one           //
//  argument: a filename, and subsequently, integers in the range 0...255     //
//  inclusive specifying byte values. It should create a file of the          //
//  specified name, containing the specified bytes.                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) { // error if not enough arguments
        printf("Error: Not enough arguments.\n");
        printf("Usage: ./create_binary_file <filename> <integers>.\n");
        return 1;
    }
    char *fname = argv[1]; // get the file name
    FILE *f = fopen(fname, "w"); // open the file to write
    
    if (f == NULL) { // error if file open is unsuccessful
        printf("Error: Could not open file.\n");
        return 1;
    }
    
    for (int i = 2; i < argc; i++) { // print each byte into the file
        int c = atoi(argv[i]);
        fputc(c, f);
    }
    
    fclose(f); // close the file
    
    return 0;
}