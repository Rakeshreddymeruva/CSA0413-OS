#include <stdio.h>

typedef struct {
    char name[4];
    int bt, wt, tat, ct;
} Proc;

int main(void) {
    Proc p[4] = {{"P1", 6, 0, 0, 0}, {"P2", 8, 0, 0, 0}, {"P3", 7, 0, 0, 0}, {"P4", 3, 0, 0, 0}};
    int n = 4;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].bt > p[j + 1].bt) {
                Proc t = p[j]; p[j] = p[j + 1]; p[j + 1] = t;
            }

    int time = 0;
    double sum_wt = 0, sum_tat = 0;
    printf("SJF CPU Scheduling Simulation\nGantt Chart: ");
    for (int i = 0; i < n; i++) {
        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        sum_wt += p[i].wt;
        sum_tat += p[i].tat;
        printf("| %s (%d-%d) ", p[i].name, p[i].wt, p[i].ct);
    }
    printf("|\n\n");

    printf("%-8s %-8s %-12s %-10s %-12s\n", "Process", "Burst", "Completion", "Waiting", "Turnaround");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
        printf("%-8s %-8d %-12d %-10d %-12d\n", p[i].name, p[i].bt, p[i].ct, p[i].wt, p[i].tat);

    printf("\nAverage Waiting Time    = %.2f\n", sum_wt / n);
    printf("Average Turnaround Time = %.2f\n", sum_tat / n);
    return 0;
}
