////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  float_less.c                                                              //   
//  -----                                                                     //
//  Compare 2 floats using bit operations only                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

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

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {

    float_components_t b1 = float_bits(bits1);
    float_components_t b2 = float_bits(bits2);
    
    // 0 is return if bits1 or bits2 is Nan
    if (is_nan(b1) || is_nan(b2)) {
        return 0;
    }
    
    if (b1.sign == b2.sign) { // if both are positive or both are negative
        if (b1.sign == 0) { // if both positive numbers
            if (b1.exponent == b2.exponent) { // if exponents are equal
                return b1.fraction < b2.fraction ? 1: 0; // compare fractions
            } else {
                return b1.exponent < b2.exponent ? 1 : 0; // check if b1 < b2
            }
        } else { // if both negative numbers
            if (b1.exponent == b2.exponent) { // if exponents are equal
                return b1.fraction > b2.fraction ? 1: 0; // compare fractions
            } else {
                return b1.exponent > b2.exponent ? 1 : 0; // check b1 < b2
            }
        }
    } else { // if one is positive and one is negative
        // if b1 is negative, b2 is positive, then b1 is less than b2, return 1
        // if b2 is negative, b1 is positive, then b2 is less than b1, return 0
        return b1.sign > b2.sign ? 1 : 0;
    }
    
    return 0;
}