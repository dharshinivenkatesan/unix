#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Child process
        char *args[] = {"./interpreter_file", "Child", NULL};
        char *envp[] = {NULL};
        execve("./interpreter_file", args, envp);
        perror("Exec failed for child");
        return EXIT_FAILURE;
    } else {
        // Parent process
        wait(NULL);
        printf("Child process completed.\n");

        // Now execute interpreter_file in parent
        char *args[] = {"./interpreter_file", "Parent", NULL};
        execve("./interpreter_file", args, NULL);
        perror("Exec failed for parent");
        return EXIT_FAILURE;
    }

    return 0;
}
