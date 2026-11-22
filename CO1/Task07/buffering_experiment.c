#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Demonstrating buffer duplication:
   When redirected to a file, stdout is fully buffered.
   Without fflush(stdout), the child inherits the buffer containing "shell: running job 2\n".
   Calling exit(3) flushes it in the child, and the parent flushes it again upon exit! */
int main(void)
{
    printf("shell: running job 1\n");
    fflush(stdout);
    
    pid_t pid = fork();
    if (pid == 0) {
        execlp("expr", "expr", "6", "*", "7", (char *)NULL);
        exit(127);
    } else {
        int status;
        waitpid(pid, &status, 0);
        printf("job 1 exit status %d\n", WEXITSTATUS(status));
    }

    printf("shell: running job 2\n");
    // fflush(stdout) intentionally omitted here
    pid = fork();
    if (pid == 0) exit(3); /* exit(3) flushes user-space stdio buffers */
    int status;
    waitpid(pid, &status, 0);
    printf("job 2 exit status %d\n", WEXITSTATUS(status));
    return 0;
}
