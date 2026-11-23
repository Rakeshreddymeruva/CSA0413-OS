#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXCYL 199
#define TOTAL_REQS 10000

static int cmp_int(const void *a, const void *b) {
    return (*(const int *)a) - (*(const int *)b);
}

typedef struct {
    double avg_move;
    int max_wait_steps;
} SimResult;

SimResult sim_fcfs(const int reqs[], int n, int qlen) {
    int pos = 100;
    long total_move = 0;
    for (int i = 0; i < n; i++) {
        total_move += abs(reqs[i] - pos);
        pos = reqs[i];
    }
    SimResult r = { (double)total_move / n, qlen - 1 };
    return r;
}

SimResult sim_sstf(const int reqs[], int n, int qlen) {
    int pos = 100;
    long total_move = 0;
    int max_wait = 0;
    for (int b = 0; b < n; b += qlen) {
        int len = (b + qlen <= n) ? qlen : (n - b);
        int done[256] = {0};
        for (int k = 0; k < len; k++) {
            int best = -1, min_d = INT_MAX;
            for (int i = 0; i < len; i++) {
                if (!done[i]) {
                    int d = abs(reqs[b + i] - pos);
                    if (d < min_d) { min_d = d; best = i; }
                }
            }
            done[best] = 1;
            total_move += min_d;
            pos = reqs[b + best];
            if (k > max_wait) max_wait = k;
        }
    }
    SimResult r = { (double)total_move / n, max_wait };
    return r;
}

SimResult sim_look(const int reqs[], int n, int qlen, int circular) {
    int pos = 100, dir = 1;
    long total_move = 0;
    int max_wait = 0;
    for (int b = 0; b < n; b += qlen) {
        int len = (b + qlen <= n) ? qlen : (n - b);
        int batch[256];
        for (int i = 0; i < len; i++) batch[i] = reqs[b + i];
        qsort(batch, len, sizeof(int), cmp_int);

        int split = 0;
        while (split < len && batch[split] < pos) split++;

        int served = 0;
        if (circular) {
            for (int i = split; i < len; i++) {
                total_move += abs(batch[i] - pos);
                pos = batch[i];
                served++;
            }
            for (int i = 0; i < split; i++) {
                total_move += abs(batch[i] - pos);
                pos = batch[i];
                served++;
            }
        } else {
            if (dir == 1) {
                for (int i = split; i < len; i++) {
                    total_move += abs(batch[i] - pos);
                    pos = batch[i];
                    served++;
                }
                for (int i = split - 1; i >= 0; i--) {
                    total_move += abs(batch[i] - pos);
                    pos = batch[i];
                    served++;
                }
            } else {
                for (int i = split - 1; i >= 0; i--) {
                    total_move += abs(batch[i] - pos);
                    pos = batch[i];
                    served++;
                }
                for (int i = split; i < len; i++) {
                    total_move += abs(batch[i] - pos);
                    pos = batch[i];
                    served++;
                }
            }
        }
        if (served - 1 > max_wait) max_wait = served - 1;
    }
    SimResult r = { (double)total_move / n, max_wait };
    return r;
}

int main(void) {
    srand(42);
    int *reqs = malloc(TOTAL_REQS * sizeof(int));
    for (int i = 0; i < TOTAL_REQS; i++) reqs[i] = rand() % (MAXCYL + 1);

    int loads[3] = {8, 32, 128};
    const char *names[3] = {"Light (q=8)", "Medium (q=32)", "Heavy (q=128)"};

    printf("=== 10,000-Request Disk Scheduling Simulation (Cylinders 0-%d) ===\n", MAXCYL);
    for (int l = 0; l < 3; l++) {
        int q = loads[l];
        SimResult r_fcfs  = sim_fcfs(reqs, TOTAL_REQS, q);
        SimResult r_sstf  = sim_sstf(reqs, TOTAL_REQS, q);
        SimResult r_look  = sim_look(reqs, TOTAL_REQS, q, 0);
        SimResult r_clook = sim_look(reqs, TOTAL_REQS, q, 1);
        printf("\nLoad: %s\n", names[l]);
        printf("  FCFS  : avg_move = %6.2f cyl/req | max_batch_wait = %3d reqs\n", r_fcfs.avg_move, r_fcfs.max_wait_steps);
        printf("  SSTF  : avg_move = %6.2f cyl/req | max_batch_wait = %3d reqs\n", r_sstf.avg_move, r_sstf.max_wait_steps);
        printf("  LOOK  : avg_move = %6.2f cyl/req | max_batch_wait = %3d reqs\n", r_look.avg_move, r_look.max_wait_steps);
        printf("  C-LOOK: avg_move = %6.2f cyl/req | max_batch_wait = %3d reqs\n", r_clook.avg_move, r_clook.max_wait_steps);
    }

    /* SSTF Starvation Experiment: stream of requests near cylinder 60 every ms */
    printf("\n=== SSTF Starvation Experiment (Pending Req at Cyl 183) ===\n");
    int head = 53;
    int pending_183_wait = 0;
    for (int ms = 1; ms <= 50; ms++) {
        int hot_req = 58 + (ms % 5); /* arrives near 60 every 1ms */
        int dist_hot = abs(hot_req - head);
        int dist_183 = abs(183 - head);
        if (dist_hot < dist_183) {
            head = hot_req;
            pending_183_wait++;
        } else {
            head = 183;
            break;
        }
    }
    printf("After 50 ms of cylinder-60 stream: request at cylinder 183 waited %d ms (STARVED!)\n", pending_183_wait);
    free(reqs);
    return 0;
}
