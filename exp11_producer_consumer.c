#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 5
#define TOTAL_ITEMS 10

int buffer[BUF_SIZE];
int in = 0, out = 0, count = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
    (void)arg;
    for (int item = 1; item <= TOTAL_ITEMS; item++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        in = (in + 1) % BUF_SIZE;
        count++;
        printf("[Producer] Produced item %2d | Buffer occupancy: %d/%d\n", item, count, BUF_SIZE);

        sem_post(&mutex);
        sem_post(&full);
        usleep(30000);
    }
    return NULL;
}

void *consumer(void *arg) {
    (void)arg;
    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        out = (out + 1) % BUF_SIZE;
        count--;
        printf("[Consumer] Consumed item %2d | Buffer occupancy: %d/%d\n", item, count, BUF_SIZE);

        sem_post(&mutex);
        sem_post(&empty);
        usleep(60000);
    }
    return NULL;
}

int main(void) {
    pthread_t prod, cons;
    sem_init(&empty, 0, BUF_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    printf("Producer-Consumer Simulation (Buffer Size = %d, Items = 1..%d)\n\n", BUF_SIZE, TOTAL_ITEMS);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    printf("\nAll %d items produced and consumed safely (buffer never exceeded %d).\n", TOTAL_ITEMS, BUF_SIZE);
    return 0;
}
