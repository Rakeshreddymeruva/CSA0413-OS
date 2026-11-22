#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3
#define CUSTOMERS 5

sem_t customers_sem, barber_sem;
pthread_mutex_t seat_mutex;
int free_chairs = CHAIRS;
int barber_sleeping = 1;
int served_count = 0;

void *barber(void *arg) {
    (void)arg;
    while (1) {
        sem_wait(&customers_sem);
        pthread_mutex_lock(&seat_mutex);
        free_chairs++;
        barber_sleeping = 0;
        printf("[Barber] Cutting hair (Free waiting chairs: %d/%d)\n", free_chairs, CHAIRS);
        pthread_mutex_unlock(&seat_mutex);

        sem_post(&barber_sem);
        usleep(120000); // Haircut duration
    }
    return NULL;
}

void *customer(void *arg) {
    int id = *(int *)arg;
    pthread_mutex_lock(&seat_mutex);
    if (free_chairs > 0) {
        int was_sleeping = (barber_sleeping && free_chairs == CHAIRS);
        free_chairs--;
        printf("[Customer %d] Arrived -> %s (Free chairs left: %d/%d)\n",
               id, was_sleeping ? "Woke barber & served immediately" : "Waiting in chair",
               free_chairs, CHAIRS);
        sem_post(&customers_sem);
        pthread_mutex_unlock(&seat_mutex);
        sem_wait(&barber_sem);
        printf("[Customer %d] Haircut finished!\n", id);
    } else {
        printf("[Customer %d] Arrived -> All %d waiting chairs full! Leaving.\n", id, CHAIRS);
        pthread_mutex_unlock(&seat_mutex);
    }
    return NULL;
}

int main(void) {
    pthread_t b_thread, c_threads[CUSTOMERS];
    int ids[CUSTOMERS] = {1, 2, 3, 4, 5};

    sem_init(&customers_sem, 0, 0);
    sem_init(&barber_sem, 0, 0);
    pthread_mutex_init(&seat_mutex, NULL);

    printf("Sleeping Barber Simulation (1 Barber, %d Waiting Chairs, %d Customers)\n\n", CHAIRS, CUSTOMERS);
    pthread_create(&b_thread, NULL, barber, NULL);
    usleep(20000);

    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_create(&c_threads[i], NULL, customer, &ids[i]);
        usleep(15000); // Rapid arrivals so chairs fill up
    }
    for (int i = 0; i < CUSTOMERS; i++) {
        pthread_join(c_threads[i], NULL);
    }
    pthread_cancel(b_thread);
    printf("\nSimulation complete.\n");
    return 0;
}
