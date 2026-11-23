#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BLOCK_SIZE 512

int main(void) {
    const char *src_file = "config.txt";
    const char *dst_file = "config_backup.txt";
    char buffer[BLOCK_SIZE];
    ssize_t bytes_read, bytes_written;
    long total_copied = 0;
    int block_num = 0;

    int src_fd = open(src_file, O_RDONLY);
    if (src_fd < 0) {
        perror("open source");
        return 1;
    }
    int dst_fd = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0) {
        perror("open dest");
        close(src_fd);
        return 1;
    }

    while ((bytes_read = read(src_fd, buffer, BLOCK_SIZE)) > 0) {
        bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(src_fd);
            close(dst_fd);
            return 1;
        }
        block_num++;
        total_copied += bytes_written;
        printf("Block %d: copied %zd bytes (Total: %ld bytes)\n", block_num, bytes_written, total_copied);
    }

    close(src_fd);
    close(dst_fd);

    // Byte-by-byte verification
    int f1 = open(src_file, O_RDONLY);
    int f2 = open(dst_file, O_RDONLY);
    char b1[BLOCK_SIZE], b2[BLOCK_SIZE];
    ssize_t r1, r2;
    int identical = 1;
    while (1) {
        r1 = read(f1, b1, BLOCK_SIZE);
        r2 = read(f2, b2, BLOCK_SIZE);
        if (r1 != r2) { identical = 0; break; }
        if (r1 == 0) break;
        for (ssize_t i = 0; i < r1; i++) {
            if (b1[i] != b2[i]) { identical = 0; break; }
        }
        if (!identical) break;
    }
    close(f1);
    close(f2);

    printf("\nCopy complete: %s -> %s (%ld bytes)\n", src_file, dst_file, total_copied);
    printf("Byte-identical verification: %s\n", identical ? "PASSED (100% match)" : "FAILED");
    return 0;
}
