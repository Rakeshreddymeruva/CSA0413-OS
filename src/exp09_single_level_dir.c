#include <stdio.h>
#include <string.h>

#define MAX_FILES 20

typedef struct {
    char name[32];
    int active;
} FileEntry;

FileEntry dir[MAX_FILES];
int file_count = 0;

void display_dir(const char *op) {
    printf("Directory Listing after [%s]: { ", op);
    int shown = 0;
    for (int i = 0; i < file_count; i++) {
        if (dir[i].active) {
            printf("%s\"%s\"", shown ? ", " : "", dir[i].name);
            shown++;
        }
    }
    printf(" } (Total: %d files)\n", shown);
}

void create_file(const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (dir[i].active && strcmp(dir[i].name, name) == 0) {
            printf("Create \"%s\": Already exists!\n", name);
            return;
        }
    }
    strcpy(dir[file_count].name, name);
    dir[file_count].active = 1;
    file_count++;
    printf("Created file \"%s\". ", name);
    display_dir("create");
}

void search_file(const char *name) {
    int found = 0;
    for (int i = 0; i < file_count; i++) {
        if (dir[i].active && strcmp(dir[i].name, name) == 0) {
            found = 1;
            break;
        }
    }
    printf("Search \"%s\": %s. ", name, found ? "FOUND" : "NOT FOUND");
    display_dir("search");
}

void delete_file(const char *name) {
    int deleted = 0;
    for (int i = 0; i < file_count; i++) {
        if (dir[i].active && strcmp(dir[i].name, name) == 0) {
            dir[i].active = 0;
            deleted = 1;
            break;
        }
    }
    printf("Delete \"%s\": %s. ", name, deleted ? "DELETED" : "NOT FOUND");
    display_dir("delete");
}

int main(void) {
    printf("Single-Level Directory Simulation\n\n");
    create_file("a.txt");
    create_file("b.txt");
    create_file("c.txt");
    search_file("b.txt");
    delete_file("b.txt");
    search_file("b.txt");
    return 0;
}
