#include <stdio.h>
#include <limits.h>

int main(void) {
    // char is by default signed
    char c = -128;
    // %d expects integer but c is type char
    // char type is converted to integer before being passed into the function
    printf("%d\n", c);

    return 0;
}