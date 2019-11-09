// hello world implemented with fwrite
 
#include <stdio.h>

int main(void) {
    char bytes[] = "Hello, Andrew!\n";

    // prints Hello, Andrew! on stdout
    fwrite(bytes, sizeof bytes[0], 15, stdout); 

    return 0;
}