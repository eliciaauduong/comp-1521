#include <stdio.h>

int main(void) {
    int x, v0;

    printf("Enter a number: ");
    scanf("%d", &x);

    v0 = x & 1;
    if (v0 == 1) goto odd;
        printf("Even\n");
    goto end;
odd:
        printf("Odd\n");
end:
    return 0;
}