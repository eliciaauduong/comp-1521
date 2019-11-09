/*
$ dcc create_append_truncate_fopen.c
$ ./a.out
open("hello.txt", "w")           -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:11 hello.txt
fputs("Hello, Andrew!\n")        -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:11 hello.txt
fclose                           -> -rw-r--r-- 1 andrewt andrewt 15 Oct 22 19:11 hello.txt
fopen("hello.txt", "a")          -> -rw-r--r-- 1 andrewt andrewt 15 Oct 22 19:11 hello.txt
fputs("Hello again, Andrew!\n")  -> -rw-r--r-- 1 andrewt andrewt 15 Oct 22 19:11 hello.txt
fflush                           -> -rw-r--r-- 1 andrewt andrewt 36 Oct 22 19:11 hello.txt
open("hello.txt", "w")           -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:11 hello.txt
fputs("Good Bye Andrew!\n")      -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:11 hello.txt
assa:files% ./a.out
open("hello.txt", "w")           -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:12 hello.txt
fputs("Hello, Andrew!\n")        -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:12 hello.txt
fclose                           -> -rw-r--r-- 1 andrewt andrewt 15 Oct 22 19:12 hello.txt
fopen("hello.txt", "a")          -> -rw-r--r-- 1 andrewt andrewt 15 Oct 22 19:12 hello.txt
fputs("Hello again, Andrew!\n")  -> -rw-r--r-- 1 andrewt andrewt 15 Oct 22 19:12 hello.txt
fflush                           -> -rw-r--r-- 1 andrewt andrewt 36 Oct 22 19:12 hello.txt
open("hello.txt", "w")           -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:12 hello.txt
fputs("Good Bye Andrew!\n")      -> -rw-r--r-- 1 andrewt andrewt 0 Oct 22 19:12 hello.txt
$ ls -l hello.txt
-rw-r--r-- 1 andrewt andrewt 17 Oct 22 19:12 hello.txt
$ cat hello.txt

Good Bye Andrew!
$
*/

#include <stdio.h>
#include <stdlib.h>

void show_file_state(char *message);

int main(int argc, char *argv[]) {
    FILE *output_stream1 = fopen("hello.txt", "w"); // no error checking

    // hello.txt will be created if it doesn't exist already
    // if hello.txt previous existed it will now contain 0 bytes

    show_file_state("open(\"hello.txt\", \"w\")");

    fputs("Hello, Andrew!\n", output_stream1);

    // the 15 bytes in "Hello, Andrew!\n" are buffered by the stdio library
    // they haven't been written to hello.txt
    // so it will still contain 0 bytes

    show_file_state("fputs(\"Hello, Andrew!\\n\")");

    fclose(output_stream1);

    // The fclose will flush the buffered bytes to hello.txt
    // hello.txt will now contain 15 bytes

    show_file_state("fclose()");

    FILE *output_stream2 = fopen("hello.txt", "a"); // no error checking

    // because "a" was specified hello.txt will not be changed
    // it will still contain 15 bytes

    show_file_state("fopen(\"hello.txt\", \"a\")");

    fputs("Hello again, Andrew!\n", output_stream2);

    // the 21 bytes in "Hello again, Andrew!\n" are buffered by the stdio library
    // they haven't been written to hello.txt
    // so it will still contain 15 bytes

    show_file_state("fputs(\"Hello again, Andrew!\\n\")");

    fflush(output_stream2);

    // The fflush will flush ahe buffered bytes to hello.txt
    // hello.txt will now contain 36 bytes

    show_file_state("fflush()");

    FILE *output_stream3 = fopen("hello.txt", "w"); // no error checking

    // because "w" was specified hello.txt will be truncated to zero length
    // hello.txt will now contain 0 bytes

    show_file_state("open(\"hello.txt\", \"w\")");

    fputs("Good Bye Andrew!\n", output_stream3);

    // the 17 bytes in "Good Bye Andrew!\" are buffered by the stdio library
    // they haven't been written to hello.txt
    // so it will still contain 0 bytes

    show_file_state("fputs(\"Good Bye Andrew!\\n\")");

    // if exit is called or main returns stdio flushes all stream
    // this will leave hello.txt with 17 bytes
    // but if a program terminates abnormally this doesn't happen

    return 0;
}

void show_file_state(char *message) {
    printf("%-32s -> ", message);
    fflush(stdout);
    system("ls -l hello.txt");
}