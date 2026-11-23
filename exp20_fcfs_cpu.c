#include <stdio.h>

int main(void) {
    const char *names[] = {"P1", "P2", "P3"};
    int bt[] = {24, 3, 3};
    int n = 3;
    int ct[3], wt[3], tat[3];
    double sum_wt = 0, sum_tat = 0;

    int time = 0;
    for (int i = 0; i < n; i++) {
        wt[i] = time;
        time += bt[i];
        ct[i] = time;
        tat[i] = ct[i]; // Arrival = 0
        sum_wt += wt[i];
        sum_tat += tat[i];
    }

    printf("FCFS CPU Scheduling Simulation\n\n");
    printf("%-8s %-8s %-12s %-10s %-12s\n", "Process", "Burst", "Completion", "Waiting", "Turnaround");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-8s %-8d %-12d %-10d %-12d\n", names[i], bt[i], ct[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time    = %.2f\n", sum_wt / n);
    printf("Average Turnaround Time = %.2f\n", sum_tat / n);
    return 0;
}
