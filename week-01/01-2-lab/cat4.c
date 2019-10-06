// COMP1521 19T3 ... lab 1
// cat4: Copy input to output

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  cat4.c                                                                    //   
//  -----                                                                     //
//  Using the most efficient method from cat1.c cat2.c and cat3.c:            //
//  - run copy(stdin, stdout) if there are no command-line arguments OR       //
//  - run copy(file, stdout) for each command-line argument                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>


static void copy(FILE *, FILE *);

int main(int argc, char *argv[]) {

    // FILE *fopen(const char *path, const char *mode)
    // FILE *fclose(FILE *fp)

    // if there are no command-line arguments
    if (argc == 1) {
        copy (stdin, stdout);
    } else {
        // for each command-line argument
        for (int i = 1; i < argc; i++) {
            // attempt to open the file
            FILE *file = fopen(argv[i], "r");
            // if the file fails to open
            if (file == NULL) {
                printf("Can't read %s", argv[i]);
            } else {
                copy (file, stdout);
                fclose(file);
            }
        }
    }
    
    return EXIT_SUCCESS;
}


// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {

    // initialise a buffer to store the input
    char ch[BUFSIZ];
    
    // while there is still input to read
    // scan input and print to output
    while (fgets(ch, BUFSIZ, input) != NULL) {
        fputs(ch, output);
    }

}