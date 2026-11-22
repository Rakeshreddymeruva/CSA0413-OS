#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <time.h>

#define N 1000

void *thread_func(void *arg) { (void)arg; return NULL; }

double get_time_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main(void) {
    printf("Benchmarking creation of %d processes vs %d threads...\n", N, N);
    
    double t0 = get_time_sec();
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        if (pid == 0) _exit(0);
        waitpid(pid, NULL, 0);
    }
    double t1 = get_time_sec();
    double proc_time = t1 - t0;
    
    pthread_t tid;
    t0 = get_time_sec();
    for (int i = 0; i < N; i++) {
        pthread_create(&tid, NULL, thread_func, NULL);
        pthread_join(tid, NULL);
    }
    t1 = get_time_sec();
    double thread_time = t1 - t0;
    
    printf("1000 Processes time: %.4f s (%.2f us/proc)\n", proc_time, (proc_time/N)*1e6);
    printf("1000 Threads time:   %.4f s (%.2f us/thread)\n", thread_time, (thread_time/N)*1e6);
    printf("Ratio (Process/Thread creation overhead): %.2fx\n", proc_time / thread_time);
    return 0;
}
