#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(void) {
    int req[] = {55, 58, 60, 70, 18};
    int n = 5;
    int head = 50;
    int disk_max = 199;

    qsort(req, n, sizeof(int), cmp);

    int split = 0;
    while (split < n && req[split] < head) split++;

    int total_movement = 0;
    int current = head;

    printf("C-SCAN Disk Scheduling Simulation (Disk Range: 0..%d)\n", disk_max);
    printf("Initial Head: %d (moving towards higher tracks)\n", head);
    printf("Head Movement Sequence: %d", head);

    // Move right (towards higher tracks)
    for (int i = split; i < n; i++) {
        total_movement += abs(req[i] - current);
        current = req[i];
        printf(" -> %d", current);
    }
    // Reach end of disk, jump to 0
    if (current != disk_max) {
        total_movement += abs(disk_max - current);
        current = disk_max;
        printf(" -> %d", current);
    }
    total_movement += abs(current - 0);
    current = 0;
    printf(" -> %d", current);

    // Service remaining requests from 0 upwards
    for (int i = 0; i < split; i++) {
        total_movement += abs(req[i] - current);
        current = req[i];
        printf(" -> %d", current);
    }

    printf("\n\nTotal Head Movement   = %d tracks\n", total_movement);
    printf("Average Head Movement = %.2f tracks\n", (double)total_movement / n);
    return 0;
}
