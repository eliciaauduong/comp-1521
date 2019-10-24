#include <stdio.h>

int main(void) {
    int x;

    printf("Enter a number: ");
    scanf("%d", &x);

    if (x % 2 == 0 || x == 7) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
}