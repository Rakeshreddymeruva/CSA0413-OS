#include <stdio.h>

int main(void) {
    int pages[] = {4, 1, 2, 4, 3, 2, 1, 5};
    int n = 8, frames_cnt = 3;
    int frames[3] = {-1, -1, -1};
    int front = 0, faults = 0;

    printf("FIFO Page Replacement Simulation (Frames = %d)\n", frames_cnt);
    printf("Reference Sequence: 4, 1, 2, 4, 3, 2, 1, 5\n\n");
    printf("%-6s %-16s %-10s\n", "Page", "Frames", "Status");
    printf("----------------------------------\n");

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames_cnt; j++) {
            if (frames[j] == pages[i]) { hit = 1; break; }
        }
        if (!hit) {
            frames[front] = pages[i];
            front = (front + 1) % frames_cnt;
            faults++;
        }
        printf("%-6d [", pages[i]);
        for (int j = 0; j < frames_cnt; j++) {
            if (frames[j] == -1) printf(" -");
            else printf(" %d", frames[j]);
        }
        printf(" ]     %s\n", hit ? "HIT" : "PAGE FAULT");
    }
    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
