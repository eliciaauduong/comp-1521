////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  float_2048.c                                                              //   
//  -----                                                                     //
//  Multiply a float by 2048 using bit operations only                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

uint32_t toNum (uint32_t n, float_components_t f);

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {

    // use & and >>
    // float_components_t has uint32_t sign, uint32_t exponent, uint32_t fraction
    float_components_t new;
    // get the sign bit
    uint32_t sMask = 2147483648;
    new.sign = (f & sMask) >> 31;
    // get the exponent bits
    uint32_t eMask = 2139095040;
    new.exponent = (f & eMask) >> 23;
    // get the fraction bits
    uint32_t fMask = 8388607;
    new.fraction = (f & fMask);
    
    return new;
}


// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {

    // mask is 10000000
    uint32_t mask = 128;
    
    // check if every digit of the exponent is 1
    int exOnes = 0;
    for (int i = 0; i < 8; i++) {
        if (f.exponent & mask) {
            exOnes = 1;
        } else {
            exOnes = 0;
            break;
        }
        mask >>= 1;
    }
    
    // check if the fraction is non-zero
    int nonZero = 0; 
    if (exOnes == 1) {
        uint32_t fMask = 4194304;
        for (int j = 0; j < 23; j++) {
            if (f.fraction & fMask) {
                nonZero = 1;
                return 1;
            } else {
                nonZero = 0;
            }
            mask >>= 1;
        }
    }
    
    if (nonZero == 0) {
        return 0;
    }
    
    return 1;
}


// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {

    // if positive
    if (f.sign == 0) {
        
        // mask is 10000000
        uint32_t mask = 128;
        
        // check if every digit of the exponent is 1
        int exOnes = 0;
        for (int i = 0; i < 8; i++) {
            if (f.exponent & mask) {
                exOnes = 1;
            } else {
                exOnes = 0;
                break;
            }
            mask >>= 1;
        }
        
        // check if the fraction is 0
        if (exOnes == 1) {
            if (f.fraction == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
        
    } else {
        return 0;
    }
    
}


// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {

    if (f.sign == 1) {
        
        // mask is 10000000
        uint32_t mask = 128;
        
        // check if every digit of the exponent is 1
        int exOnes = 0;        
        for (int i = 0; i < 8; i++) {
            if (f.exponent & mask) {
                exOnes = 1;
            } else {
                exOnes = 0;
                break;
            }
            mask >>= 1;
        }
        
        // check if the fraction is 0
        if (exOnes == 1) {
            if (f.fraction == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
        
    } else {
        return 0;
    }
}


// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {

    if (f.exponent == 0 && f.fraction == 0) {
        return 1;
    } else {
        return 0;
    }
}

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -int, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {

    // separate components of a float
    float_components_t flo = float_bits(f);
    // check if the number is 0, -0, inf, -inf or NaN
    if (is_zero(flo) || 
        is_nan(flo) || 
        is_positive_infinity(flo) || 
        is_negative_infinity(flo)) {
        return f;
    }
    
    uint32_t num = (flo.sign << 31); // set the number to be + or -
    
    if ((flo.exponent + 11) > 0xff) { // if f * 2048 >= +- infinity
        // set the number to infinity
        flo.exponent = 0xff << 23;
        flo.fraction = 0;
        return toNum(num, flo);
    } else { // otherwise multiply by 2048
        flo.exponent = (flo.exponent + 11) << 23;
        return toNum(num, flo);
    }
}

// store components of a float into a 32 bit int
uint32_t toNum (uint32_t n, float_components_t f) {
    n = n | f.exponent;
    n = n | f.fraction;
    return n;
}