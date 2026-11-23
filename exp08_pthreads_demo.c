#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int id;
    int early_exit;
} ThreadArg;

void *worker(void *arg) {
    ThreadArg *ta = (ThreadArg *)arg;
    pthread_t self_id = pthread_self();

    for (int i = 1; i <= 3; i++) {
        printf("[Thread T%d] Iteration %d | pthread_self() = %lu\n",
               ta->id, i, (unsigned long)self_id);
        if (ta->early_exit && i == 1) {
            printf("[Thread T%d] Calling pthread_exit() early after 1 iteration!\n", ta->id);
            pthread_exit(NULL);
        }
        usleep(50000);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2, t3;
    pthread_t t1_copy;
    ThreadArg a1 = {1, 0}, a2 = {2, 1}, a3 = {3, 0};

    pthread_create(&t1, NULL, worker, &a1);
    t1_copy = t1;
    pthread_create(&t2, NULL, worker, &a2);
    pthread_create(&t3, NULL, worker, &a3);

    printf("[Main] Checking pthread_equal(T1, T1_copy): %s\n",
           pthread_equal(t1, t1_copy) ? "TRUE (same thread handle)" : "FALSE");
    printf("[Main] Checking pthread_equal(T1, T2):      %s\n\n",
           pthread_equal(t1, t2) ? "TRUE" : "FALSE (different threads)");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n[Main] All 3 threads joined successfully. Program exiting.\n");
    return 0;
}
