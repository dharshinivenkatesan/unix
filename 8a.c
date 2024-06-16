#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void remove_empty_files(const char *dirname) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char filepath[256];

    dir = opendir(dirname);
    if (dir == NULL) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    printf("Removing empty files from directory: %s\n", dirname);

    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

        if (stat(filepath, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Check if it's a regular file and if it's empty (size == 0)
        if (S_ISREG(file_stat.st_mode) && file_stat.st_size == 0) {
            printf("Removing empty file: %s\n", filepath);
            if (unlink(filepath) == -1) {
                perror("unlink");
                continue;
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *dirname = argv[1];

    remove_empty_files(dirname);

    printf("Empty files removed successfully.\n");

    return EXIT_SUCCESS;
}
