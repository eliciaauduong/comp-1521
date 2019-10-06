////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  Elicia Au Duong (z5260173)                                                //
//  bcd_add.c                                                                 //   
//  -----                                                                     //
//  Given 2 arbitrary length BCD values, calculate the sum                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

//
// Store an arbitray length Binary Coded Decimal number.
// bcd points to an array of size n_bcd
// Each array element contains 1 decimal digit.
// Digits are stored in reverse order.
//
// For example if 42 is stored then
// n_bcd == 2
// bcd[0] == 0x02
// bcd[1] == 0x04
//

typedef struct big_bcd {
    unsigned char *bcd;
    int n_bcd;
} big_bcd_t;


big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y);
void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
big_bcd_t *bcd_from_string(char *string);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <number>\n", argv[0]);
        exit(1);
    }

    big_bcd_t *left = bcd_from_string(argv[1]);
    big_bcd_t *right = bcd_from_string(argv[2]);

    big_bcd_t *result = bcd_add(left, right);

    bcd_print(result);
    printf("\n");

    bcd_free(left);
    bcd_free(right);
    bcd_free(result);

    return 0;
}


// DO NOT CHANGE THE CODE ABOVE HERE



big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y) {  
    
    // find the length of each number
    int xLen = x->n_bcd;
    int yLen = y->n_bcd;
    // find the larger of two numbers
    int xLarge = 1;
    int largeLen = xLen;
    if (xLen < yLen) {
        largeLen = yLen;
        xLarge = 0;
    } 
    
    // if the two numbers are not the same length
    if (xLen != yLen) {
        if (xLarge == 1) { // if the length of x is greater than length of y
            y->bcd = realloc(y->bcd, xLen); // set y length to x length
            y->n_bcd = xLen;
            // set each extra value to 0
            int j = yLen;
            while (j < xLen) {
                y->bcd[j] = 0;
                j++;
            }
        } else { // the length of y is greater than x
            x->bcd = realloc(x->bcd, yLen); // set x length to y length
            x->n_bcd = yLen;
            // set each extra value to 0
            int k = xLen;
            while (k < yLen) {
                x->bcd[k] = 0;
                k++;
            }
        }
    }
    
    // create a new array to store the sum of numbers
    big_bcd_t *new = malloc(sizeof(big_bcd_t));
    new->n_bcd = largeLen;
    new->bcd = malloc(largeLen * sizeof(char));
    // set every value of the new array to 0
    for (int i = 0; i < largeLen; i++) {
        new->bcd[i] = 0;
    }

    int carry = 0;
    int sum = 0;

    // for every digit of the numbers
    for (int i = 0; i < largeLen; i++) {
        // calculate the sum of the two digits
        int xVal = x->bcd[i];
        int yVal = y->bcd[i];
        sum = xVal + yVal;
        // if the sum is a two digit number, store the one's digit
        new->bcd[i] = ((sum + carry) % 10);
        // if the sum is two digits, carry 1
        if ((sum + carry) >= 10) {
            carry = 1;
        } else {
            carry = 0;
        }
        
    }
    
    // if the sum of the final digits is greater than 9 (i.e. 2 digits)
    // allocate an extra element to store the final digit
    // the final digit can only be 1 since the greatest total of the previous
    // two numbers is 9 + 9 = 18 with 1 in the tens digit
    if (carry == 1) {
        new->bcd = realloc(new->bcd, largeLen + 1); 
        new->n_bcd++;
        new->bcd[largeLen] = 1;
    }
    
    return new;
}


// DO NOT CHANGE THE CODE BELOW HERE


// print a big_bcd_t number
void bcd_print(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}

// free storage for big_bcd_t number
void bcd_free(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    // or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t *bcd_from_string(char *string) {
    big_bcd_t *number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}