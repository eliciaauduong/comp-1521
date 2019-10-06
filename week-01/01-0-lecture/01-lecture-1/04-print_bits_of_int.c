// Print binary representation of ints 
#include <stdio.h>

int main(void) {
    while (1) {
        int a;
        printf("Enter an int: ");
        // scanf returns the number of things it can read
        // won't return 1 if non-integer (e.g. letters) or no bytes
        scanf("%d", &a);
        int j = 8 * (sizeof a); // sizeof is an operator, take a type / variable
        while (j > 0) {
            j = j - 1;
            // >> is a bitwise shift, moves the bits of a across j positions
            // & is a bitwise operation: gives the jth bit of an integer value
            printf("%d", (a >> j) & 1); // prints bits 32 to 1 of an integer
        }
        printf("\n");
    }

}

// 65535
// 00000000000000001111111111111111
// 1
// 00000000000000000000000000000001
// -1 
// 11111111111111111111111111111111
// -2
// 11111111111111111111111111111110
// -4 
// 11111111111111111111111111111100