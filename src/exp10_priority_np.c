#include <stdio.h>

typedef struct {
    char name[4];
    int burst;
    int priority;
    int wt;
    int tat;
    int ct;
} Proc;

int main(void) {
    Proc p[3] = {
        {"P1", 30, 2, 0, 0, 0},
        {"P2",  5, 1, 0, 0, 0},
        {"P3", 12, 3, 0, 0, 0}
    };
    int n = 3;

    // Sort by priority (lower number = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                Proc tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }

    int time = 0;
    double total_wt = 0, total_tat = 0;
    printf("Non-Preemptive Priority Scheduling (Lower = Higher Priority)\n");
    printf("Execution Order: ");
    for (int i = 0; i < n; i++) {
        p[i].wt = time;
        time += p[i].burst;
        p[i].ct = time;
        p[i].tat = p[i].ct; // Arrival = 0
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf("%s%s", p[i].name, (i < n - 1) ? " -> " : "\n\n");
    }

    printf("%-8s %-8s %-10s %-12s %-12s %-14s\n",
           "Process", "Burst", "Priority", "Completion", "Waiting", "Turnaround");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-8s %-8d %-10d %-12d %-12d %-14d\n",
               p[i].name, p[i].burst, p[i].priority, p[i].ct, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time    = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    return 0;
}
