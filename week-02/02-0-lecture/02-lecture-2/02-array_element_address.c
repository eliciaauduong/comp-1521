#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main(void) {
    double array[10];

    for (int i = 0; i < 10; i++) {
        printf("&array[%d]=%p\n", i, &array[i]);
    }

    printf("\nexample computation for address of array element \\n\n");

    uint64_t a = (uint64_t)&array[0];
    printf("&array[0] + 7 * sizeof (double) = 0x%lx\n",     a + 7 * sizeof (double));
    printf("&array[0] + 7 * %lx               = 0x%lx\n", sizeof (double), a + 7 * sizeof (double));
    printf("0x%lx + 7 * %lx          = 0x%lx\n", a, sizeof (double), a + 7 * sizeof (double));
    printf("&array[7]                       = %p\n", &array[7]);
}