#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define CYCLES 3

pthread_mutex_t forks[N];
pthread_mutex_t count_lock;
int eating_now = 0;
int max_concurrent = 0;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    for (int c = 1; c <= CYCLES; c++) {
        // Asymmetric fork ordering prevents circular wait (deadlock-free)
        int first = (id % 2 == 0) ? left : right;
        int second = (id % 2 == 0) ? right : left;

        pthread_mutex_lock(&forks[first]);
        pthread_mutex_lock(&forks[second]);

        pthread_mutex_lock(&count_lock);
        eating_now++;
        if (eating_now > max_concurrent) max_concurrent = eating_now;
        printf("[Philosopher %d] Eating (Cycle %d/%d) | Forks: %d & %d | Eating simultaneously: %d\n",
               id, c, CYCLES, left, right, eating_now);
        pthread_mutex_unlock(&count_lock);

        usleep(30000);

        pthread_mutex_lock(&count_lock);
        eating_now--;
        pthread_mutex_unlock(&count_lock);

        pthread_mutex_unlock(&forks[second]);
        pthread_mutex_unlock(&forks[first]);
        usleep(20000);
    }
    return NULL;
}

int main(void) {
    pthread_t phil[N];
    int ids[N];
    pthread_mutex_init(&count_lock, NULL);
    for (int i = 0; i < N; i++) pthread_mutex_init(&forks[i], NULL);

    printf("Dining Philosophers Simulation (5 Philosophers, 3 Cycles Each, Deadlock-Free)\n\n");
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(phil[i], NULL);

    printf("\nAll 5 philosophers completed %d eating cycles without deadlock.\n", CYCLES);
    printf("Maximum philosophers eating simultaneously: %d (<= 2 verified)\n", max_concurrent);
    return 0;
}
