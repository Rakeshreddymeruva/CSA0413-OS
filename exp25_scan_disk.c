#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main(void) {
    int req[] = {55, 58, 60, 70, 18, 90, 150, 160, 184};
    int n = 9, head = 50, disk_max = 199;

    qsort(req, n, sizeof(int), cmp);
    int split = 0;
    while (split < n && req[split] < head) split++;

    int total = 0, curr = head;
    printf("SCAN Disk Scheduling Simulation (Disk Range: 0..%d)\n", disk_max);
    printf("Initial Head: %d (moving towards higher tracks)\n", head);
    printf("Head Movement Sequence: %d", head);

    for (int i = split; i < n; i++) {
        total += abs(req[i] - curr);
        curr = req[i];
        printf(" -> %d", curr);
    }
    if (curr != disk_max) {
        total += abs(disk_max - curr);
        curr = disk_max;
        printf(" -> %d", curr);
    }
    for (int i = split - 1; i >= 0; i--) {
        total += abs(req[i] - curr);
        curr = req[i];
        printf(" -> %d", curr);
    }

    printf("\n\nTotal Head Movement   = %d tracks\n", total);
    printf("Average Head Movement = %.2f tracks\n", (double)total / n);
    return 0;
}
