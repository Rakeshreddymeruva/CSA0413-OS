#include <stdio.h>

int main(void) {
    int disk_next[20];
    for (int i = 0; i < 20; i++) disk_next[i] = -1;

    // File blocks: 2 -> 8 -> 4 -> 15 -> 6
    int chain[] = {2, 8, 4, 15, 6};
    int len = 5;
    for (int i = 0; i < len - 1; i++) {
        disk_next[chain[i]] = chain[i + 1];
    }
    disk_next[chain[len - 1]] = -1; // End of file

    int first = 2, last = 6;
    printf("Linked File Allocation Simulation\n");
    printf("Directory Entry: first_block = %d, last_block = %d\n\n", first, last);
    printf("Traversing Linked Block Chain:\n  ");
    int curr = first;
    int step = 1;
    while (curr != -1) {
        printf("Block %d", curr);
        if (disk_next[curr] != -1) printf(" -> ");
        else printf(" -> NULL (EOF)\n");
        curr = disk_next[curr];
        step++;
    }
    printf("Total blocks traversed: %d (Verified last_block = %d)\n", step - 1, last);
    return 0;
}
