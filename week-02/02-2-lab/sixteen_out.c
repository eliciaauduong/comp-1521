//
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  sixteen_out.c                                                             //   
//  -----                                                                     //
//  Convert from decimal to binary using bitwise operations                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {

    // allocate storage for a null-terminated string
    char *binary = malloc(sizeof(char)*(N_BITS+1));
    binary[N_BITS]='\0';
    signed int mask = 1;
    // loop through each digit (from right to left)
    for (int i = N_BITS - 1; i >= 0; i--) {
        if (value & mask) { // if there is a '1' in the position
            binary[i] = '1'; // set the position in the string to '1'
        } else { // otherwise set the position in the string to '0'
            binary[i] = '0';
        }
        // don't shift mask for the last digit
        if (i != 0) {
            mask = mask << 1;
        }
    }

    return binary;
}
