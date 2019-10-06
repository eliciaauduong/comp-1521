//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  sixteen_in.c                                                              //   
//  -----                                                                     //
//  Convert from binary to decimal using bitwise operations                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {

    int16_t num = 0;
    int16_t mask = 1;
    // loop for each digit (from right to left)
    for (int i = N_BITS - 1; i >= 0; i--) {
        if (bits[i] == '1') { // if there is a '1' in the position 
            num = num | mask; // set the digit to one in the number
        }
        // don't shift mask for the last digit
        if (i != 0) {
            mask = mask << 1;
        }
    }
    
    return num;
}
