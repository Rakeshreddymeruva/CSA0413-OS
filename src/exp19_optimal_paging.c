#include <stdio.h>

int main(void) {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = 20, f = 3;
    int frames[3] = {-1, -1, -1};
    int faults = 0;

    printf("Optimal Page Replacement Simulation (Frames = %d)\n", f);
    printf("%-6s %-16s %-12s\n", "Page", "Frames", "Status");
    printf("------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) { hit = 1; break; }
        }
        if (!hit) {
            int pos = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) { pos = j; break; }
            }
            if (pos == -1) {
                int farthest = -1;
                for (int j = 0; j < f; j++) {
                    int next_use = n + 1;
                    for (int k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) { next_use = k; break; }
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        pos = j;
                    }
                }
            }
            frames[pos] = pages[i];
            faults++;
        }
        printf("%-6d [", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1) printf(" -");
            else printf(" %d", frames[j]);
        }
        printf(" ]     %s\n", hit ? "HIT" : "PAGE FAULT");
    }
    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
