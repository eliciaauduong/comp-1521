////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  packed_bcd.c                                                              //   
//  -----                                                                     //
//  Convert from packed BCD to integer with bitwise operations                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    // mask starts from scanning in the first digit (4 bits)
    uint32_t mask = 4026531840; // 1111 0000 0000 0000 0000 0000 0000 00000
    uint32_t total = 0;
    int value = 0;
    
    // go through each 'digit' of packed_bcd value
    for (int i = 7; i >= 0; i--) {
        // calculate the value of each digit by aligning to the first 4 digits
        value = (packed_bcd_value & mask) >> (4 * i);
        // if the value isn't 1 multiply each digit by the power of 10
        if (value != 0) {
            // calculate the power of 10
            uint32_t digits = 1;
            for (int j = 0; j < i; j++) {
                digits *= 10;
            }
            // multiply the digit by the power of 10 and add it to the total
            total += value * digits;
        }
        // move the mask to the next digit to check
        mask = mask >> 4;
    }

    return total;
}