#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TOTAL_CAMERAS 64
#define FRAMES_PER_CAMERA 1000

long shared_counter_unprotected = 0;
long shared_counter_protected = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start_cam;
    int end_cam;
} WorkerArg;

void *worker_func(void *arg) {
    WorkerArg *w = (WorkerArg *)arg;
    for (int c = w->start_cam; c < w->end_cam; c++) {
        for (int f = 0; f < FRAMES_PER_CAMERA; f++) {
            // Unprotected race condition demonstration
            shared_counter_unprotected++;
            
            // Protected increment
            pthread_mutex_lock(&count_mutex);
            shared_counter_protected++;
            pthread_mutex_unlock(&count_mutex);
        }
    }
    return NULL;
}

double run_pool(int pool_size) {
    shared_counter_unprotected = 0;
    shared_counter_protected = 0;
    pthread_t threads[pool_size];
    WorkerArg args[pool_size];
    
    struct timespec ts1, ts2;
    clock_gettime(CLOCK_MONOTONIC, &ts1);
    
    int chunk = TOTAL_CAMERAS / pool_size;
    for (int i = 0; i < pool_size; i++) {
        args[i].start_cam = i * chunk;
        args[i].end_cam = (i == pool_size - 1) ? TOTAL_CAMERAS : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, worker_func, &args[i]);
    }
    for (int i = 0; i < pool_size; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &ts2);
    return (ts2.tv_sec - ts1.tv_sec) + (ts2.tv_nsec - ts1.tv_nsec) * 1e-9;
}

int main(void) {
    printf("Processing %d cameras (%d frames total)...\n", TOTAL_CAMERAS, TOTAL_CAMERAS * FRAMES_PER_CAMERA);
    int pools[] = {1, 4, 8, 16};
    double base_time = 0;
    for (int i = 0; i < 4; i++) {
        int p = pools[i];
        double t = run_pool(p);
        if (p == 1) base_time = t;
        printf("Pool Size %2d: Time = %.4fs, Speedup = %.2fx | Protected = %ld (Expected %d), Unprotected = %ld\n",
               p, t, base_time / t, shared_counter_protected, TOTAL_CAMERAS * FRAMES_PER_CAMERA, shared_counter_unprotected);
    }
    return 0;
}
