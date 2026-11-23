#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
    const char *old_name = "old.txt";
    const char *new_name = "new.txt";

    // 1. Create old.txt
    int fd = open(old_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd >= 0) {
        write(fd, "Sample data\n", 12);
        close(fd);
        printf("1. Create \"%s\"        : SUCCESS\n", old_name);
    }

    // 2. Check existence
    printf("2. Exists \"%s\"        : %s\n", old_name, access(old_name, F_OK) == 0 ? "YES" : "NO");

    // 3. Rename old.txt -> new.txt
    if (rename(old_name, new_name) == 0) {
        printf("3. Rename to \"%s\"     : SUCCESS\n", new_name);
    }

    // 4. Change permissions to read-only (chmod 444)
    if (chmod(new_name, 0444) == 0) {
        struct stat st;
        stat(new_name, &st);
        printf("4. chmod 444 \"%s\"     : SUCCESS (mode = %o)\n", new_name, st.st_mode & 0777);
    }

    // 5. Attempt to delete new.txt
    if (unlink(new_name) == 0) {
        printf("5. Delete \"%s\"        : SUCCESS (unlink succeeded; directory write perm allows removal)\n", new_name);
    } else {
        perror("5. Delete failed");
    }
    return 0;
}
