#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void print_bytes(void *v, int n);

struct s1 {
    uint8_t    c1;
    uint64_t   l1;
    uint8_t    c2;
    uint64_t   l2;
    uint8_t    c3;
    uint64_t   l3;
    uint8_t    c4;
    uint64_t   l4;
};

struct s2 {
    uint64_t   l1;
    uint64_t   l2;
    uint64_t   l3;
    uint64_t   l4;
    uint8_t    c1;
    uint8_t    c2;
    uint8_t    c3;
    uint8_t    c4;
};

int main(void) {
    struct s1 v1;
    struct s2 v2;

    printf("sizeof v1 = %lu\n", sizeof v1);
    printf("sizeof v2 = %lu\n", sizeof v2);

    printf("alignment rules mean struct s1 is padded\n");

    printf("&(v1.c1) = %p\n", &(v1.c1));
    printf("&(v1.l1) = %p\n", &(v1.l1));
    printf("&(v1.c2) = %p\n", &(v1.c2));
    printf("&(v1.l2) = %p\n", &(v1.l2));

    printf("struct s2 is not padded\n");

    printf("&(v2.c1) = %p\n", &(v2.l1));
    printf("&(v2.l1) = %p\n", &(v2.l2));
}