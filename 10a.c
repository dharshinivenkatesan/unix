#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

// Function to initialize daemon process
void init_daemon() {
    pid_t pid;
    int fd;

    // Fork off the parent process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // If we got a good PID, then we can exit the parent process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask (umask)
    umask(0);

    // Create a new session ID for the child process
    if (setsid() < 0) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    // Change the working directory to the root directory
    if (chdir("/") < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Redirect standard file descriptors to /dev/null
    fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2 stdin");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2 stdout");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDERR_FILENO) == -1) {
        perror("dup2 stderr");
        exit(EXIT_FAILURE);
    }
    if (fd > STDERR_FILENO) {
        if (close(fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    // Now the process is a daemon
    printf("Daemon process initialized. PID: %d\n", getpid());

    // Example: Daemon process can do its work here
    // Replace with your daemon's main logic

    // Example: Sleep for demonstration
    while (1) {
        sleep(30); // Daemon process main work loop
    }
}

int main() {
    // Initialize as a daemon process
    init_daemon();

    return 0;
}
