// Print hexadecimal directly (without using printf) using bitwise operators to 
// extract digits 

#include <stdio.h>
#include <stdio.h>

void print_hex(int n);

int main(void) {
    int a = 0;
    printf("Enter an int: ");
    scanf("%d", &a);
    printf("%d = 0x", a);
    print_hex(a);
    printf("\n");
    return 0;
}


void print_hex(int n) {
    int which_digit =  2 * (sizeof n) - 1;
    while (which_digit >= 0) {
        int digit = (n >> (4 * which_digit)) & 0xF;
        int ascii = "0123456789ABCDEF"[digit];
        putchar(ascii);
        which_digit--;
    }
}