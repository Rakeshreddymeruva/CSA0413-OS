#include <stdio.h>

typedef struct {
    char name[4];
    int at, bt, prio, rem, ct, wt, tat;
} Proc;

int main(void) {
    Proc p[5] = {
        {"P1", 0, 10, 3, 10, 0, 0, 0},
        {"P2", 1,  1, 1,  1, 0, 0, 0},
        {"P3", 2,  2, 4,  2, 0, 0, 0},
        {"P4", 3,  1, 5,  1, 0, 0, 0},
        {"P5", 4,  5, 2,  5, 0, 0, 0}
    };
    int n = 5, completed = 0, time = 0, prev = -1;

    printf("Preemptive Priority Scheduling (Lower = Higher Priority)\n");
    printf("Gantt Chart:\n  ");

    while (completed < n) {
        int best = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem > 0) {
                if (best == -1 || p[i].prio < p[best].prio) best = i;
            }
        }
        if (best != -1) {
            if (best != prev) {
                if (prev != -1) printf("(%d) | ", time);
                printf("%s(%d-", p[best].name, time);
                prev = best;
            }
            p[best].rem--;
            time++;
            if (p[best].rem == 0) {
                p[best].ct = time;
                p[best].tat = p[best].ct - p[best].at;
                p[best].wt = p[best].tat - p[best].bt;
                completed++;
            }
        } else {
            time++;
        }
    }
    printf("%d)\n\n", time);

    double sum_wt = 0, sum_tat = 0;
    printf("%-8s %-8s %-8s %-10s %-12s %-10s %-12s\n",
           "Process", "Arrival", "Burst", "Priority", "Completion", "Waiting", "Turnaround");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
        printf("%-8s %-8d %-8d %-10d %-12d %-10d %-12d\n",
               p[i].name, p[i].at, p[i].bt, p[i].prio, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time    = %.2f\n", sum_wt / n);
    printf("Average Turnaround Time = %.2f\n", sum_tat / n);
    return 0;
}
