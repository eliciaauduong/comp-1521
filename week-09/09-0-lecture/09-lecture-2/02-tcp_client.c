// A simple TCP client

// For more explanation see: https://github.com/angrave/SystemProgramming/wiki/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(void) {

    // create a IPv4 TCP/IP socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints = {
        .ai_family = AF_INET,        /* IPv4 only */
        .ai_socktype = SOCK_STREAM,  /* TCP */
    };

    // we wish to connect to port 1521 on our local machine
    // first convert it to a struct addrinfo

    struct addrinfo *a;
    int s = getaddrinfo("localhost", "1521", &hints, &a);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }

    // then try to establish a connection
    if (connect(sock_fd, a->ai_addr, a->ai_addrlen) == -1) {
        perror("connect");
        exit(2);
    }

    char *message = "My name is Ingo Montoya";
    printf("SENDING: %s\n", message);

    write(sock_fd, message, strlen(message));

    char response[1000];
    int n_bytes = read(sock_fd, response, (sizeof response) - 1);
    response[n_bytes] = '\0';
    printf("RESPONSE WAS: %s\n", response);

    close(sock_fd);

    return 0;
}