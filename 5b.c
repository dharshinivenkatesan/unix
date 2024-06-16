#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int signum) {
    printf("Caught SIGINT signal (%d).\n", signum);
    // Reset the default action for SIGINT
    signal(SIGINT, SIG_DFL);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Install signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("SIGINT handler installed. Press Ctrl+C to trigger.\n");

    // Sleep to allow time to trigger SIGINT
    sleep(10);

    printf("Resetting default action for SIGINT.\n");

    // Reset SIGINT to default action (terminate program)
    signal(SIGINT, SIG_DFL);

    // Sleep again to demonstrate default action
    sleep(10);

    printf("End of program.\n");

    return EXIT_SUCCESS;
}
