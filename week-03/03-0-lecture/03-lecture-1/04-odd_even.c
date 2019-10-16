#include <stdio.h>

int main(void) {
    int x;

    printf("Enter a number: ");
    scanf("%d", &x);

    if ((x & 1) == 0) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
}