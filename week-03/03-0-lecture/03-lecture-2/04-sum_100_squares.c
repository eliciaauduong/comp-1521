#include <stdio.h>

// sum of first 100 squares.

int main(void) {
    int sum = 0;

    for (int i = 0; i <= 100; i++) {
        sum += i * i;
    }

    printf("%d\n", sum);
}