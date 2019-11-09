// non-portable code illustrating 2d-array indexing
// this relies on pointers being implemented by memory addresses
// which most compiled C implementations do

#include <stdio.h>
#include <stdint.h>


uint32_t array[3][4] = {{10, 11, 12, 13}, {14, 15, 16, 17}, {18, 19, 20, 21}};

int main(void) {
    // use a typecast to assign array address to integer variable i
    uint64_t i = (uint64_t)&array;

    // i += (2 * 16) + 2 * 4
    i += (2 * sizeof array[0]) + 2 * sizeof array[0][0];

    // use a typecast to assign  i to a pointer vaiable
    uint32_t *y = (uint32_t *)i;

    printf("*y = %d\n", *y); // prints 20
}