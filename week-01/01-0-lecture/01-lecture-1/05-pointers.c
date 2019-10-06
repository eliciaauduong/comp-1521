#include <stdio.h>

int main(void) {
    
    int *p = NULL; // initialise a pointer before you use it
    printf("%p\n", p);

    // print the bits of the pointer
    // In C program, can't have something in address 0
    printf("%lx\n", (long)p); 

    // show the bytes of a pointer for the address of where i is in memory
    int i;
    int *point = &i;
    printf("%lx\n", (long)point);
}