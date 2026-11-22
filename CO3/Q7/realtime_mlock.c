#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

#define LOOP_COUNT 100000
#define ARRAY_SIZE (1024 * 1024)

static char buffer[ARRAY_SIZE];

double measure_access(void) {
    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
    for (int i = 0; i < LOOP_COUNT; i++) {
        buffer[(i * 64) % ARRAY_SIZE] += 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &t2);
    return (t2.tv_sec - t1.tv_sec) * 1e6 + (t2.tv_nsec - t1.tv_nsec) * 1e-3; /* in us */
}

int main(void) {
    printf("=== Real-Time Memory Locking Demonstration (mlock) ===\n");
    printf("Measuring memory access WITHOUT mlock...\n");
    double time_unlocked = measure_access();
    printf("Unlocked loop execution time: %.2f us\n", time_unlocked);

    printf("Locking memory frames via mlock()...\n");
    if (mlock(buffer, sizeof(buffer)) != 0) {
        perror("mlock");
    } else {
        printf("Memory frames locked into physical RAM successfully.\n");
    }
    double time_locked = measure_access();
    printf("Locked loop execution time:   %.2f us\n", time_locked);
    munlock(buffer, sizeof(buffer));
    return 0;
}
