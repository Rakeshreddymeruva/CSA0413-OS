#include <stdio.h>

int main(void) {
    int disk[16];
    for (int i = 0; i < 8; i++) disk[i] = 1;  // 0-7 reserved for iNodes
    for (int i = 8; i < 16; i++) disk[i] = 0; // 8-15 available

    int files[2] = {4, 3}; // File 1: 4 KB (4 blocks), File 2: 3 KB (3 blocks)
    const char *names[2] = {"File_A (4 KB)", "File_B (3 KB)"};

    printf("Contiguous File Allocation Simulation (16 Blocks x 1 KB)\n");
    printf("Blocks 0-7: Reserved for iNodes | Blocks 8-15: Available\n\n");

    for (int f = 0; f < 2; f++) {
        int len = files[f], start = -1;
        for (int i = 8; i <= 16 - len; i++) {
            int ok = 1;
            for (int j = 0; j < len; j++) {
                if (disk[i + j] != 0) { ok = 0; break; }
            }
            if (ok) { start = i; break; }
        }
        if (start != -1) {
            for (int j = 0; j < len; j++) disk[start + j] = 1;
            printf("Allocated %-15s -> Start Block: %2d, Length: %d blocks (Blocks %d-%d)\n",
                   names[f], start, len, start, start + len - 1);
        } else {
            printf("Failed to allocate %s\n", names[f]);
        }
    }
    return 0;
}
