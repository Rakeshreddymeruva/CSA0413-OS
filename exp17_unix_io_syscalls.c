#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main(void) {
    struct stat st;
    if (stat("data.txt", &st) == 0) {
        printf("1. stat(\"data.txt\"):\n");
        printf("   File Size       : %ld bytes\n", (long)st.st_size);
        printf("   Permission Bits : %o (octal)\n\n", st.st_mode & 0777);
    }

    int fd = open("data.txt", O_RDONLY);
    if (fd >= 0) {
        int flags = fcntl(fd, F_GETFL);
        printf("2. fcntl(fd, F_GETFL) : 0x%x (Read-only mode verified)\n", flags & O_ACCMODE);

        lseek(fd, 10, SEEK_SET);
        char buf[6] = {0};
        ssize_t n = read(fd, buf, 5);
        printf("3. lseek(fd, 10, SEEK_SET) + read(5 bytes): \"%s\" (%zd bytes read)\n\n", buf, n);
        close(fd);
    }

    printf("4. opendir(\".\") / readdir() entries:\n   ");
    DIR *dp = opendir(".");
    struct dirent *entry;
    int count = 0;
    while ((entry = readdir(dp)) != NULL) {
        printf("%s  ", entry->d_name);
        count++;
    }
    printf("\n   (Total entries: %d)\n", count);
    closedir(dp);
    return 0;
}
