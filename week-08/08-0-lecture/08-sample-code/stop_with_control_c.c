// simple example of catching a signal don't compile with dcc 

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int signal_received = 0;

void stop(int signum) {
    signal_received = 1;
}

int main(void) {
    // catch SIGINT which is sent if user types cntrl-C
    struct sigaction action = {.sa_handler = stop};
    sigaction(SIGUSR1, &action, NULL);

    while (!signal_received) {
        printf("Type ctrl-c to stop me\n");
        sleep(1);
    }
    printf("Good bye\n");
}