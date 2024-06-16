#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to print file details
void print_file_details(const char *filename) {
    struct stat file_stat;

    // Get file statistics
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file statistics");
        exit(EXIT_FAILURE);
    }

    // Print file details
    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", file_stat.st_size);
    printf("Blocks: %ld\n", file_stat.st_blocks);
    printf("Last access time: %s", ctime(&file_stat.st_atime));
    printf("Last modification time: %s", ctime(&file_stat.st_mtime));
    printf("Last status change time: %s", ctime(&file_stat.st_ctime));
}

int main(int argc, char *argv[]) {
    // Check if filename is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Print file details
    print_file_details(argv[1]);

    return 0;
}
