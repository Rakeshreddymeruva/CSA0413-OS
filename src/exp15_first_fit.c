#include <stdio.h>

int main(void) {
    int partitions[] = {40, 10, 30, 60};
    int orig_part[]  = {40, 10, 30, 60};
    int m = 4;
    int processes[]  = {100, 50, 30, 120, 35};
    int n = 5;
    int allocated[5];

    for (int i = 0; i < n; i++) {
        allocated[i] = -1;
        for (int j = 0; j < m; j++) {
            if (partitions[j] >= processes[i]) {
                allocated[i] = j;
                partitions[j] -= processes[i];
                break;
            }
        }
    }

    printf("First-Fit Memory Allocation Simulation\n");
    printf("Initial Partitions (KB): 40, 10, 30, 60\n\n");
    printf("%-10s %-14s %-18s %-15s\n", "Process", "Size (KB)", "Partition", "Remaining (KB)");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (allocated[i] != -1) {
            int p_idx = allocated[i];
            printf("P%-9d %-14d Partition %d (%d KB)  %d KB\n",
                   i + 1, processes[i], p_idx + 1, orig_part[p_idx], partitions[p_idx]);
        } else {
            printf("P%-9d %-14d %-18s %s\n",
                   i + 1, processes[i], "Not Allocated", "-");
        }
    }
    return 0;
}
