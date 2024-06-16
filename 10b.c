#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process with PID: %d\n", getpid());
        printf("Child process is sleeping for 3 seconds...\n");
        sleep(3);
        printf("Child process exiting...\n");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process with PID: %d\n", getpid());

        // Using wait
        printf("Parent process waiting for any child to terminate...\n");
        pid_t terminated_pid = wait(&status);
        if (terminated_pid == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("Child process with PID %d exited with status: %d\n", terminated_pid, WEXITSTATUS(status));
        }

        // Fork another child process
        pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Another child process with PID: %d\n", getpid());
            printf("Another child process is sleeping for 5 seconds...\n");
            sleep(5);
            printf("Another child process exiting...\n");
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            printf("Parent process with PID: %d\n", getpid());

            // Using waitpid
            printf("Parent process waiting for child with PID %d to terminate...\n", pid);
            pid_t terminated_pid = waitpid(pid, &status, 0);
            if (terminated_pid == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(status)) {
                printf("Child process with PID %d exited with status: %d\n", terminated_pid, WEXITSTATUS(status));
            }
        }
    }

    return 0;
}
