#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGES 1000
#define PAGE_SIZE 4096

int main(void) {
    printf("=== Demand Paging Memory Access Pattern Simulation ===\n");
    volatile char *mem = (volatile char *)malloc(PAGES * PAGE_SIZE);
    if (!mem) { perror("malloc"); return 1; }

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    /* Sequential access (strong spatial locality) */
    for (int p = 0; p < PAGES; p++) {
        mem[p * PAGE_SIZE] = (char)(p % 256);
    }
    clock_gettime(CLOCK_MONOTONIC, &t2);
    double seq_time = (t2.tv_sec - t1.tv_sec) * 1e6 + (t2.tv_nsec - t1.tv_nsec) * 1e-3;

    clock_gettime(CLOCK_MONOTONIC, &t1);
    /* Random access (stride access / zero spatial locality) */
    for (int p = 0; p < PAGES; p++) {
        int idx = (p * 509) % PAGES;
        mem[idx * PAGE_SIZE] += 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &t2);
    double rand_time = (t2.tv_sec - t1.tv_sec) * 1e6 + (t2.tv_nsec - t1.tv_nsec) * 1e-3;

    printf("Sequential Touch Time: %.2f us\n", seq_time);
    printf("Random Touch Time:     %.2f us\n", rand_time);
    printf("Demand Paging Locality Efficiency: Sequential is %.2fx faster due to TLB & Page Cache prefetching\n",
           rand_time / seq_time);

    free((void *)mem);
    return 0;
}
