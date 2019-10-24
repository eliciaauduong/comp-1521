#include <stdio.h>
#include <stdint.h>

/*
$ clang stack_inspect.c
$ a.out
 0: Address 0x7ffe1766c304 contains 3           <- a[0]
 1: Address 0x7ffe1766c308 contains 5           <- x
 2: Address 0x7ffe1766c30c contains 2a          <- b
 3: Address 0x7ffe1766c310 contains 1766c330    <- f  frame pointer (64 bit)
 4: Address 0x7ffe1766c314 contains 7ffe
 5: Address 0x7ffe1766c318 contains 40120c      <- f return address
 6: Address 0x7ffe1766c31c contains 0
 7: Address 0x7ffe1766c320 contains 22
 8: Address 0x7ffe1766c324 contains 25
 9: Address 0x7ffe1766c328 contains 9           <- a
10: Address 0x7ffe1766c32c contains 0
11: Address 0x7ffe1766c330 contains 401220      <- main return address
12: Address 0x7ffe1766c334 contains 0
13: Address 0x7ffe1766c338 contains c7aca09b    <- main frame pointer (64 bit)
14: Address 0x7ffe1766c33c contains 7ff3
15: Address 0x7ffe1766c340 contains 0
*/

void f(int b) {
    int x = 5;
    uint32_t a[1] = {3};

    for (int i = 0; i < 16; i++)
        printf("%2d: Address %p contains %x\n", i, &a[i], a[0+i]);
}

int main(void) {
    int a = 9;
    printf("function main is at address %p\n", &main);
    printf("function f is at address %p\n", &f);
    f(42);
    return 0;
}