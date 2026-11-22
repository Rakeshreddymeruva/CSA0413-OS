#include <stdio.h>
#include <unistd.h>
#include "encrypt_lib.h"

int main(void) {
    char secret[] = "CustomerAcc#987654321-Balance-$50000";
    char encrypted[64];
    encrypt_data(secret, encrypted);
    printf("Original Data:  %s\n", secret);
    printf("Encrypted Data: %s\n", encrypted);
    printf("PID: %d (inspect /proc/%d/maps to view loaded address space)\n", getpid(), getpid());
    return 0;
}
