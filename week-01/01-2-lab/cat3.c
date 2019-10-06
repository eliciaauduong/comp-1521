// COMP1521 19T3 ... lab 1
// cat3: Copy input to output

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  cat3.c                                                                    //   
//  -----                                                                     //
//  Using fgets and fputs to copy input to output, character by character     //
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

    // char *fgets(char *s, int size, FILE *stream)
    // char *fputs(const char *s, FILE *stream)

    // initialise a buffer to store the input
    char ch[BUFSIZ];
    
    // while there is still input to read
    // scan input and print to output
    while (fgets(ch, BUFSIZ, input) != NULL) {
        fputs(ch, output);
    }
    
}