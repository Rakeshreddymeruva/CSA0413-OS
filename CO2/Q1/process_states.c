#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    printf("Parent PID: %d\n", getpid());
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        printf("Child PID: %d created. Inspect in /proc/%d/status.\n", getpid(), getpid());
        sleep(2);
        printf("Child exiting.\n");
        _exit(0);
    } else {
        printf("Parent waiting for child PID %d...\n", pid);
        waitpid(pid, NULL, 0);
        printf("Child reaped. Parent exiting.\n");
    }
    return 0;
}
