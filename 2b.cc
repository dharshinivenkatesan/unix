#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Function to print file flags
void print_file_flags(int fd) {
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Error getting file flags");
        exit(EXIT_FAILURE);
    }

    // Print access mode
    int accessMode = flags & O_ACCMODE;
    switch (accessMode) {
        case O_RDONLY:
            printf("Access mode: Read only\n");
            break;
        case O_WRONLY:
            printf("Access mode: Write only\n");
            break;
        case O_RDWR:
            printf("Access mode: Read/Write\n");
            break;
        default:
            printf("Unknown access mode\n");
            break;
    }

    // Print other flags
    if (flags & O_APPEND) {
        printf("Flag: Append\n");
    }
    if (flags & O_NONBLOCK) {
        printf("Flag: Non-blocking\n");
    }
    if (flags & O_SYNC) {
        printf("Flag: Synchronous writes\n");
    }
    if (flags & O_DSYNC) {
        printf("Flag: Synchronous data writes\n");
    }
    if (flags & O_RSYNC) {
        printf("Flag: Synchronous reads\n");
    }
}

int main(int argc, char *argv[]) {
    // Check if file descriptor is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_descriptor>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Convert the argument to an integer
    int fd = atoi(argv[1]);

    // Print file flags
    print_file_flags(fd);

    return 0;
}
