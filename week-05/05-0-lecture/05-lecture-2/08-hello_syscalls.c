// hello world implemented with direct syscall 

#include <unistd.h>

int main(void) {
    char bytes[16] = "Hello, Andrew!\n";

    // argument 1 to syscall is  system call number, 1 == write
    // remaining arguments are specific to each system call

    // write system call takes 3 arguments:
    //   1) file descriptor, 1 == stdout // 0 stdin, 2 stderr 
    //   2) memory address of first byte to write
    //   3) number of bytes to write

    syscall(1, 1, bytes, 15); // prints Hello, Andrew! on stdout

    return 0;
}