#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("[Child Process]  Own PID = %d, Parent PID (PPID) = %d\n", getpid(), getppid());
        printf("[Child Process]  Task completed. Exiting...\n");
        exit(0);
    } else {
        printf("[Parent Process] Own PID = %d, Parent PID (PPID) = %d, Created Child PID = %d\n",
               getpid(), getppid(), pid);
        int status;
        wait(&status);
        printf("[Parent Process] Child (PID %d) finished with exit status %d. Parent exiting.\n",
               pid, WEXITSTATUS(status));
    }
    return 0;
}
