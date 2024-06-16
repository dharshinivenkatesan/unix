#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Get parent process ID
    pid_t parent_pid = getpid();

    // Create a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process created with PID: %d\n", getpid());

        // Execute a program to demonstrate access function
        execl("/bin/ls", "ls", "-l", NULL);  // Example: List files in current directory
        perror("execl");  // Should not reach here if exec is successful
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process with PID: %d\n", parent_pid);
        printf("Waiting for child process with PID: %d\n", pid);

        // Wait for the child process to exit
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally\n");
        }
    }

    return 0;
}
