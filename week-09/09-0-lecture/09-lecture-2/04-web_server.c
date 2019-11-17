// A simple Web server

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char **argv) {

    // create a IPv4 TCP/IP socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE,
    };

    // we wish to wait for connections on port 1521 on our local machine
    // first convert it to a struct addrinfo
    struct addrinfo *a;
    int s = getaddrinfo(NULL, "1080", &hints, &a);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(1);
    }

    // attach the address to the socket
    if (bind(sock_fd, a->ai_addr, a->ai_addrlen) != 0) {
        perror("bind()");
        return 1;
    }

    // specify the maximum number of connections that can be queued for the socket
    if (listen(sock_fd, 16) != 0) {
        perror("listen()");
        return 1;
    }

    printf("Connect to me at http://localhost:1080/\n");
    int client_fd;
    while ((client_fd = accept(sock_fd, NULL, NULL)) >= 0) {

        // a real server might spawn a client process here to handle the connection
        // so it can accept another connection immediately

        printf("Connection made: client_fd=%d\n", client_fd);

        char message[1024];
        int n_bytes = read(client_fd, message, (sizeof message) - 1);
        message[n_bytes] = '\0';
        printf("READ %d BYTES: %s\n", n_bytes, message);

        printf("SENDING BACK ASCII ART\n");

        char *header = "HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n\r\n";
        write(client_fd, header, strlen(header));

        char *body = "\n |\\/\\/\\/|  \n |      |  \n |      |  \n | (o)(o)  \n C      _) \n  | ,___|  \n  |   /    \n /____\\    \n/      \\\n";
        write(client_fd, body, strlen(body));
        close(client_fd);
    }


    close(sock_fd);

    return 0;
}