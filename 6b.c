#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FILE_PATH "testfile.txt"
#define LOCK_START -100
#define LOCK_LEN 100
#define READ_LEN 50

void print_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void print_lock_info(struct flock *fl) {
    if (fl->l_type == F_UNLCK) {
        printf("Region is not locked. Locking it now.\n");
    } else {
        printf("Region is locked.\n");
        printf("Process ID of the locking process: %d\n", fl->l_pid);
    }
}

int main() {
    int fd;
    struct flock fl;
    char buffer[READ_LEN + 1]; // +1 for null terminator

    // Open the file
    fd = open(FILE_PATH, O_RDWR);
    if (fd == -1)
        print_error("open");

    // Set up the lock structure
    memset(&fl, 0, sizeof(struct flock));
    fl.l_type = F_WRLCK;   // Exclusive write lock
    fl.l_whence = SEEK_END;
    fl.l_start = LOCK_START;
    fl.l_len = LOCK_LEN;

    // Check if the region is locked
    if (fcntl(fd, F_GETLK, &fl) == -1)
        print_error("fcntl F_GETLK");

    // Print lock information
    print_lock_info(&fl);

    // If the region is not locked, lock it and read the last 50 bytes
    if (fl.l_type == F_UNLCK) {
        // Lock the region
        if (fcntl(fd, F_SETLK, &fl) == -1)
            print_error("fcntl F_SETLK");

        // Move file pointer to the start of the region to read
        if (lseek(fd, LOCK_START + LOCK_LEN - READ_LEN, SEEK_END) == -1)
            print_error("lseek");

        // Read the last 50 bytes
        ssize_t bytes_read = read(fd, buffer, READ_LEN);
        if (bytes_read == -1)
            print_error("read");
        buffer[bytes_read] = '\0'; // Null-terminate the string

        printf("Read last %ld bytes: %s\n", bytes_read, buffer);

        // Unlock the region
        fl.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLK, &fl) == -1)
            print_error("fcntl F_SETLK");
    }

    // Close the file
    if (close(fd) == -1)
        print_error("close");

    return 0;
}
