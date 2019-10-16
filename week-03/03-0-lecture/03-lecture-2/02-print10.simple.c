#include <stdio.h>

int main(void) {
    int i;
    i = 1;
loop:
    if (i > 10) goto end;
        printf("%d", i);
        printf("\n");
        i++;
    goto loop;
end:
    return 0;
}