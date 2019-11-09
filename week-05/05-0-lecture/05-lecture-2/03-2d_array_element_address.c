#include <stdio.h>

#define X 3
#define Y 4

int main(void) {
    int array[X][Y];

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            array[x][y] = x + y;
        }
    }

    for (int x = 0; x < X; x++) {
        for (int y = 0; y < Y; y++) {
            printf("%d ", array[x][y]);
        }
        printf("\n");
    }

    printf("sizeof array[2][3] = %lu\n", sizeof array[2][3]);
    printf("sizeof array[1] = %lu\n", sizeof array[1]);
    printf("sizeof array = %lu\n", sizeof array);

    printf("&array=%p\n", &array);
    for (int x = 0; x < X; x++) {
        printf("&array[%d]=%p\n", x, &array[x]);
        for (int y = 0; y < Y; y++) {
            printf("&array[%d][%d]=%p\n", x, y, &array[x][y]);
        }
    }
}

/*
    Change this to a 1d array
    ``
    int array[X][Y];
    ``
    Then we get
    ``
    int array[X * Y];
    ``
    and access each element with
    ``
    array[x*Y + y]; 
    ``
*/