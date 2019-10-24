/* 
Run at CSE like this

$ gcc-7 invalid0.c -o invalid0
$ ./invalid0
42 42 42 77 77 77 77 77 77 77
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a[10];
    int b[10];
    printf("a[0] is at address %p\n",&a[0]);
    printf("a[9] is at address %p\n", &a[9]);
    printf("b[0] is at address %p\n",&b[0]);
    printf("b[9] is at address %p\n", &b[9]);

    for (int i = 0; i < 10; i++) {
        a[i] = 77;
    }

    // loop writes to b[10] .. b[12] which don't exist -
    // with gcc 7.3 on x86_64/Linux
    // b[12] is stored where a[0] is stored
    // with gcc 7 on CSE lab machines
    // b[10] is stored where a[0] is stored

    for (int i = 0; i <= 12; i++) {
        b[i] = 42;
    }

    // prints 42 77 77 77 77 77 77 77 77 77 on x86_64/Linux
    // prints 42 42 42 77 77 77 77 77 77 77 at CSE
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}