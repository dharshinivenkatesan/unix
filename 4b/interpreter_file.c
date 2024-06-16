#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    char *args[] = {"./echoall", argv[1], NULL};
    execve("./echoall", args, envp);
    perror("Exec failed");
    return EXIT_FAILURE;
}
