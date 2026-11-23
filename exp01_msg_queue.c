#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main(void) {
    key_t key = ftok("/tmp", 65);
    if (key == -1) {
        key = 12345;
    }
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Sender Process
        const char *messages[] = {"START", "DATA:100", "END"};
        struct msg_buffer msg;
        msg.msg_type = 1;
        printf("[Sender PID %d] Sending 3 messages of type 1 to queue (ID: %d)...\n", getpid(), msgid);
        for (int i = 0; i < 3; i++) {
            strncpy(msg.msg_text, messages[i], sizeof(msg.msg_text) - 1);
            msg.msg_text[sizeof(msg.msg_text) - 1] = '\0';
            if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) {
                perror("msgsnd");
                exit(1);
            }
            printf("[Sender] Sent: \"%s\"\n", msg.msg_text);
        }
        exit(0);
    } else {
        // Receiver Process
        wait(NULL);
        struct msg_buffer msg;
        printf("[Receiver PID %d] Reading messages from queue (ID: %d)...\n", getpid(), msgid);
        for (int i = 0; i < 3; i++) {
            if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) {
                perror("msgrcv");
                return 1;
            }
            printf("[Receiver] Received (type %ld): \"%s\"\n", msg.msg_type, msg.msg_text);
        }
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl");
            return 1;
        }
        printf("[Receiver] Message queue (ID: %d) removed successfully.\n", msgid);
    }
    return 0;
}
