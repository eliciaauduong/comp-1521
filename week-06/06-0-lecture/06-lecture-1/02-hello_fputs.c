// hello world implemented with fputs 

#include <stdio.h>

int main(void) {
    char bytes[] = "Hello, Andrew!\n";

    fputs(bytes, stdout); // relies on bytes being nul-terminated

    return 0;
}