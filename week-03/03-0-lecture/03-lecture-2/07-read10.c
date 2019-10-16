#include <stdio.h>

int
main(void) {
    int i;
    int numbers[10] = {0};

    i = 0;
    while (i < 10) {
        printf("Enter a number: ");
        scanf("%d", &numbers[i]);
        i++;
    }
    i = 0;
    while (i < 10) {
        printf("%d\n", numbers[i]);
        i++;
    }
    return 0;
}