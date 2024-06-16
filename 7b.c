#include <stdio.h>
#include <stdlib.h>

void print_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    FILE *source_file, *dest_file;
    char ch;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open source file for reading
    source_file = fopen(argv[1], "r");
    if (source_file == NULL) {
        print_error("Error opening source file");
    }

    // Open destination file for writing
    dest_file = fopen(argv[2], "w");
    if (dest_file == NULL) {
        print_error("Error opening destination file");
    }

    // Copy contents from source to destination
    while ((ch = fgetc(source_file)) != EOF) {
        if (fputc(ch, dest_file) == EOF) {
            print_error("Error writing to destination file");
        }
    }

    printf("File copied successfully.\n");

    // Close files
    if (fclose(source_file) == EOF) {
        print_error("Error closing source file");
    }
    if (fclose(dest_file) == EOF) {
        print_error("Error closing destination file");
    }

    return EXIT_SUCCESS;
}
