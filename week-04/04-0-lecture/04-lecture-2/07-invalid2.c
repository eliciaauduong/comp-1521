/*
Run at CSE like this

$ gcc-7 invalid2.c -o invalid2
$ ./invalid2
answer=42
*/

#include <stdio.h>

void f(int x);

int main(void) {
    int answer = 36;
    printf("answer is stored at address %p\n", &answer);

    f(5);
    printf("answer=%d\n", answer); // prints 42 not 36

    return 0;
}

void f(int x) {
    int a[10];

    // a[19] doesn't exist
    // with gcc-7 at CSE variable answer in main
    // happens to be where a[19] would be

    printf("a[19] would be stored at address %p\n", &a[19]);

    a[19] = 42;
}