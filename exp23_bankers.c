#include <stdio.h>

int main(void) {
    int n = 4, m = 3;
    int alloc[4][3] = {{1,0,0}, {6,1,2}, {2,1,1}, {0,0,2}};
    int max[4][3]   = {{3,2,2}, {6,1,3}, {3,1,4}, {4,2,2}};
    int avail[3]    = {1, 1, 2};
    int need[4][3], finish[4] = {0}, safe_seq[4];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("Banker's Algorithm Deadlock Avoidance\n");
    printf("Initial Available: [%d, %d, %d]\n\n", avail[0], avail[1], avail[2]);
    printf("Process   Alloc       Max         Need\n");
    for (int i = 0; i < n; i++) {
        printf("P%-7d  [%d,%d,%d]     [%d,%d,%d]     [%d,%d,%d]\n",
               i, alloc[i][0], alloc[i][1], alloc[i][2],
               max[i][0], max[i][1], max[i][2],
               need[i][0], need[i][1], need[i][2]);
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int ok = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) { ok = 0; break; }
                }
                if (ok) {
                    for (int j = 0; j < m; j++) avail[j] += alloc[i][j];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    if (count == n) {
        printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
        for (int i = 0; i < n; i++) printf("P%d%s", safe_seq[i], (i < n - 1) ? " -> " : "\n");
    } else {
        printf("\nSystem is in an UNSAFE STATE!\n");
    }
    return 0;
}
