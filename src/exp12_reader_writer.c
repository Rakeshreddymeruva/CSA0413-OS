#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readcount = 0;
int shared_data = 100;

void *reader(void *arg) {
    int id = *(int *)arg;
    for (int cycle = 1; cycle <= 2; cycle++) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("[Reader %d] Reading shared_data = %d (Active readers: %d)\n",
               id, shared_data, readcount);
        usleep(40000);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&wrt);
        sem_post(&mutex);

        usleep(50000);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    for (int cycle = 1; cycle <= 2; cycle++) {
        sem_wait(&wrt);
        shared_data += 50;
        printf("[Writer %d] Updated shared_data to %d (Exclusive access, active readers: %d)\n",
               id, shared_data, readcount);
        usleep(40000);
        sem_post(&wrt);
        usleep(60000);
    }
    return NULL;
}

int main(void) {
    pthread_t r[3], w;
    int r_ids[3] = {1, 2, 3};
    int w_id = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    printf("Reader-Writer Synchronization (3 Readers, 1 Writer)\n\n");
    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &r_ids[i]);
    pthread_create(&w, NULL, writer, &w_id);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    pthread_join(w, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    printf("\nReader-Writer simulation completed with zero read/write conflicts.\n");
    return 0;
}
