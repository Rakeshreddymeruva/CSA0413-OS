#include <stdio.h>

int main(void) {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = 13, f = 3;
    int frames[3] = {-1, -1, -1};
    int last_used[3] = {-1, -1, -1};
    int faults = 0;

    printf("LRU Page Replacement Simulation (Frames = %d)\n", f);
    printf("%-6s %-16s %-12s\n", "Page", "Frames", "Status");
    printf("------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int hit_idx = -1;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) { hit_idx = j; break; }
        }
        if (hit_idx != -1) {
            last_used[hit_idx] = i;
        } else {
            int pos = 0;
            for (int j = 1; j < f; j++) {
                if (last_used[j] < last_used[pos]) pos = j;
            }
            frames[pos] = pages[i];
            last_used[pos] = i;
            faults++;
        }
        printf("%-6d [", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1) printf(" -");
            else printf(" %d", frames[j]);
        }
        printf(" ]     %s\n", (hit_idx != -1) ? "HIT" : "PAGE FAULT");
    }
    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
