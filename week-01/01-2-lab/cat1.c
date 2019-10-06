// COMP1521 19T3 ... lab 1
// cat1: Copy input to output

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  cat1.c                                                                    //   
//  -----                                                                     //
//  Using fscanf and fprintf to copy input to output, character by character  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

static void copy(FILE *, FILE *);

int main(void) {
    copy (stdin, stdout);
    return EXIT_SUCCESS;
}

// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {

    // int fscanf(FILE *stream, const char *format, ...)
    // int fprintf(FILE *stream, const char *format, ...)

    // initialise a variable to store the character
    char ch; 
    
    // while there is still input to read
    // scan in the input and print in output
    while (fscanf(input, "%c", &ch) != EOF) {
        fprintf(output, "%c", ch);
    }
}