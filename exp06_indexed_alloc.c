#include <stdio.h>

int main(void) {
    int index_block[] = {3, 7, 2, 9, 5, 11};
    int n = 6;
    int req_block_1based = 4;

    printf("Indexed File Allocation Simulation\n");
    printf("File Size: %d blocks | Index Block Location: Block 0\n\n", n);
    printf("Index Block Table:\n");
    printf("  Logical Block (0-based / 1-based)  ->  Physical Disk Block\n");
    printf("  ----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("  Index[%d] (Block #%d)               ->  Disk Block %d\n", i, i + 1, index_block[i]);
    }

    printf("\nResolving Request for File's 4th Block:\n");
    printf("  4th Block (1-based, index = %d) -> Physical Disk Block %d\n",
           req_block_1based - 1, index_block[req_block_1based - 1]);
    return 0;
}
