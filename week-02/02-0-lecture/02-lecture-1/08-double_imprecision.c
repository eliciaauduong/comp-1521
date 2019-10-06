// The value 0.1 can not be precisely represented as a double 
// As a result b != 0 

#include <stdio.h>
#include <math.h>

int main(void) {
    double a, b;

    a = 0.1;
    b = 1 - (a + a + a + a + a + a + a + a + a + a);

    if (fabs(b) > 0.000000000001) {
        printf("1 != 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1\n");
    } else {
        printf("1 == 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1\n");
    }

    printf("b = %.16f\n", b);

    return 0;
}