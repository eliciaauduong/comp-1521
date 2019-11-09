// non-portable code illustrating array indexing
// this relies on pointers being implemented by memory addresses
// which most compiled C implementations do

#include <stdio.h>
#include <stdint.h>

uint32_t array[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

int main(void) {
    // use a typecast to assign array address to integer variable i
    uint64_t i = (uint64_t)&array;

    i += 7 * sizeof array[0]; // add 28 to i

    // use a typecast to assign  i to a pointer variable
    uint32_t *y = (uint32_t *)i;

    printf("*y = %d\n", *y); // prints 17

    // compare to pointer arithmetic where adding 1
    // moves to the next array element
    uint32_t *z = array;
    z += 7;
    printf("*z = %d\n", *z); // prints 17
}