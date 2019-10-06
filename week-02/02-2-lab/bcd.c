////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  bcd.c                                                                     //   
//  -----                                                                     //
//  Convert from unpacked BCD to decimal using bitwise operations             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {

    // get the binary value for the ten digit
    int maskOne = -255; // 1111 0000
    // get the binary value for the ones digit
    int maskTwo = 255; // 0000 1111
    
    int num = 0;
    // get the tens digit and ones digit and add them together
    num = ((bcd_value & maskOne) >> 8) * 10 + (bcd_value & maskTwo);
    
    return num;
}
