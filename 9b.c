#include <stdio.h>
#include <stdlib.h>

void display_file_content(const char *filename) {
    FILE *fp;
    int ch;
    long file_size;

    // Open the file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read and display first 20 characters
    printf("\nFirst 20 characters from %s:\n", filename);
    for (int i = 0; i < 20; ++i) {
        ch = fgetc(fp);
        if (ch == EOF) {
            break;
        }
        putchar(ch);
    }

    // Seek to 10th byte from the beginning
    fseek(fp, 10, SEEK_SET);

    // Display 20 characters from the 10th byte
    printf("\n\n20 characters from 10th byte from %s:\n", filename);
    for (int i = 0; i < 20; ++i) {
        ch = fgetc(fp);
        if (ch == EOF) {
            break;
        }
        putchar(ch);
    }

    // Seek 10 bytes ahead from current file offset
    fseek(fp, 10, SEEK_CUR);

    // Display 20 characters from current position + 10 bytes
    printf("\n\n20 characters from current position + 10 bytes from %s:\n", filename);
    for (int i = 0; i < 20; ++i) {
        ch = fgetc(fp);
        if (ch == EOF) {
            break;
        }
        putchar(ch);
    }

    // Get file size
    fseek(fp, 0, SEEK_END); // Move to end of file
    file_size = ftell(fp);  // Get current position (file size)
    if (file_size == -1) {
        perror("ftell");
    } else {
        printf("\n\nFile size of %s: %ld bytes\n", filename, file_size);
    }

    // Close the file
    fclose(fp);
}

int main() {
    const char *filename = "example.txt";

    // Display file content and perform seek operations
    display_file_content(filename);

    return 0;
}
