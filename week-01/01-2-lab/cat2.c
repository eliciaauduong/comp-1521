// COMP1521 19T3 ... lab 1
// cat2: Copy input to output

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  cat2.c                                                                    //   
//  -----                                                                     //
//  Using fgetc and fputc to copy input to output, character by character     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

static void copy(FILE *, FILE *);

int main(void) {
    copy (stdin, stdout);
    return EXIT_SUCCESS;
}

// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {

    // int fgetc(FILE *stream)
    // int fputc(int c, FILE *stream)

    // get the first character of the input
    int ch = fgetc(input);
    
    // while the character is not end of file
    while (ch != EOF) {
        // print character to output
        fputc(ch, output);
        // scan in the next character
        ch = fgetc(input);
    }
}