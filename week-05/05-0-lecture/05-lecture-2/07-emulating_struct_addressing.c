// non-portable code illustrating access to a struct field
// this relies on pointers being implemented by memory addresses
// which most compiled C implementations do

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct simple {
    char     c;
    uint32_t i;
    double   d;
};

struct simple s = { 'Z', 42, 3.14159 };

int main(void) {
    // use a typecast to assign struct address to integer variable i
    uint64_t i = (uint64_t)&s;

    // 3 bytes of padding - likely but not guaranteed
    i += (sizeof s.c) + 3;
    // use a typecast to assign  i to a pointer vaiable
    uint32_t *y = (uint32_t *)i;

    printf("*y = %d\n", *y); // prints 42
}