#include <stdio.h>

// sum of first 100 squares.

int main(void) {
    int i, sum, t3;

    sum = 0;
    i = 0;
    loop:
       if (i > 100) goto end;
       t3 = i * i;
       sum = sum + t3;
       i = i + 1;
    goto loop;

end:
    printf("%d", sum);
    printf("\n");
}