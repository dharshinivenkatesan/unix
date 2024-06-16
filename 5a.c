#include <stdio.h>
#include <stdlib.h>
#include <utime.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *destination_file = argv[2];

    struct stat stat_source;
    if (stat(source_file, &stat_source) == -1) {
        perror("Failed to get file status");
        return EXIT_FAILURE;
    }

    struct utimbuf utime_buf;
    utime_buf.actime = stat_source.st_atime; // Access time
    utime_buf.modtime = stat_source.st_mtime; // Modification time

    if (utime(destination_file, &utime_buf) == -1) {
        perror("Failed to set file timestamps");
        return EXIT_FAILURE;
    }

    printf("Timestamps copied successfully from %s to %s.\n", source_file, destination_file);

    return EXIT_SUCCESS;
}
