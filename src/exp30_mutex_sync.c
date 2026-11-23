#include <stdio.h>
#include <pthread.h>

#define INCREMENTS 100000

long counter = 0;
pthread_mutex_t lock;

void *increment_worker(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    printf("[Thread %d] Completed %d synchronized increments.\n", id, INCREMENTS);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_mutex_init(&lock, NULL);
    printf("Mutex Lock Thread Synchronization (2 Threads x %d Increments)\n\n", INCREMENTS);

    pthread_create(&t1, NULL, increment_worker, &id1);
    pthread_create(&t2, NULL, increment_worker, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);

    printf("\nExpected Counter Value : %d\n", 2 * INCREMENTS);
    printf("Final Counter Value    : %ld\n", counter);
    printf("Synchronization Status : %s\n", (counter == 2 * INCREMENTS) ? "EXACT MATCH (No Race Condition)" : "MISMATCH");
    return 0;
}
