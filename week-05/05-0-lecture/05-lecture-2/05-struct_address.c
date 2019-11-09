#include <stdio.h>
#include <stdint.h>

struct s1 {
    uint32_t   i0;
    uint32_t   i1;
    uint32_t   i2;
    uint32_t   i3;
};

struct s2 {
    uint8_t    b;
    uint64_t   l;
};

int main(void) {
    struct s1 v1;

    printf("&v1      = %p\n", &v1);
    printf("&(v1.i0) = %p\n", &(v1.i0));
    printf("&(v1.i1) = %p\n", &(v1.i1));
    printf("&(v1.i2) = %p\n", &(v1.i2));
    printf("&(v1.i3) = %p\n", &(v1.i3));

    printf("\nThis shows struct padding\n");

    struct s2 v2;
    printf("&v2      = %p\n", &v2);
    printf("&(v2.b)  = %p\n", &(v2.b));
    printf("&(v2.l)  = %p\n", &(v2.l));
}