#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void print_perms(mode_t mode, char *str) {
    str[0] = S_ISDIR(mode) ? 'd' : '-';
    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';
    str[10] = '\0';
}

int main(int argc, char *argv[]) {
    int long_fmt = 0;
    const char *dir_path = ".";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            long_fmt = 1;
        } else {
            dir_path = argv[i];
        }
    }

    DIR *dp = opendir(dir_path);
    if (!dp) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char full_path[512];
    char perm[11];

    if (long_fmt) {
        printf("%-12s %-10s %s\n", "Permissions", "Size (B)", "Name");
        printf("------------------------------------\n");
    }

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        if (long_fmt) {
            snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
            struct stat st;
            if (stat(full_path, &st) == 0) {
                print_perms(st.st_mode, perm);
                printf("%-12s %-10ld %s\n", perm, (long)st.st_size, entry->d_name);
            }
        } else {
            printf("%s  ", entry->d_name);
        }
    }
    if (!long_fmt) printf("\n");

    closedir(dp);
    return 0;
}
