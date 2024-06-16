#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
    int i;

    printf("Program: %s\n", argv[0]);
    printf("Received arguments:\n");
    for (i = 1; i < argc && argv[i] != NULL; ++i) {
        printf("  %s\n", argv[i]);
    }

    printf("\nReceived environment variables:\n");
    for (i = 0; envp[i] != NULL; ++i) {
        printf("  %s\n", envp[i]);
    }

    return 0;
}
