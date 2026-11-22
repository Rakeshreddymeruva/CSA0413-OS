#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int queue[] = {82, 170, 43, 140, 24, 16, 190};
    int n = sizeof(queue) / sizeof(queue[0]);
    int head = 50;
    int total_movement = 0;

    printf("FCFS Disk Scheduling Simulation\n");
    printf("Initial Head Position: %d\n", head);
    printf("Request Queue: ");
    for (int i = 0; i < n; i++) printf("%d%s", queue[i], (i < n - 1) ? ", " : "\n");

    printf("\nHead Movement Sequence:\n");
    printf("%d", head);
    int current = head;
    for (int i = 0; i < n; i++) {
        int diff = abs(queue[i] - current);
        total_movement += diff;
        current = queue[i];
        printf(" -> %d", current);
    }
    printf("\n\nStep-by-step Seek Distance:\n");
    current = head;
    for (int i = 0; i < n; i++) {
        int diff = abs(queue[i] - current);
        printf("  Move %3d -> %3d : %3d tracks\n", current, queue[i], diff);
        current = queue[i];
    }
    printf("\nTotal Head Movement = %d tracks\n", total_movement);
    printf("Average Head Movement = %.2f tracks\n", (double)total_movement / n);
    return 0;
}
