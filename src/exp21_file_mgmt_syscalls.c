#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    const char *filename = "log.txt";
    const char *msg = "Service started";
    char buf[64] = {0};

    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) { perror("open write"); return 1; }
    ssize_t w = write(fd, msg, strlen(msg));
    printf("1. Opened \"%s\" with O_CREAT|O_WRONLY; wrote %zd bytes: \"%s\"\n", filename, w, msg);
    close(fd);
    printf("2. Closed file descriptor %d.\n", fd);

    fd = open(filename, O_RDONLY);
    if (fd < 0) { perror("open read"); return 1; }
    ssize_t r = read(fd, buf, sizeof(buf) - 1);
    buf[r] = '\0';
    printf("3. Reopened \"%s\" with O_RDONLY; read %zd bytes back: \"%s\"\n", filename, r, buf);
    close(fd);
    return 0;
}
