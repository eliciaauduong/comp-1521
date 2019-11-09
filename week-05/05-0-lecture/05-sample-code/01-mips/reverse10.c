// read 10 integers then print them in reverse order

#include <stdio.h>

int numbers[10];

int main() {
    int count;

    count = 0;
    while (count < 10) {
        printf("Enter a number: ");
        scanf("%d", &numbers[count]);
        count++;
    }

    printf("Reverse order:\n");
    count = 9;
    while (count >= 0) {
        printf("%d\n", numbers[count]);
        count--;
    }

    return 0;
}