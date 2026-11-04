#include <stdio.h>

typedef struct {
    int base;
    int limit;
    const char *name;
} Segment;

Segment seg_table[5] = {
    {219, 600, "Segment 0 (Code - Read Only)"},
    {2300, 14, "Segment 1 (Data - Read/Write)"},
    {90, 100, "Segment 2 (Stack - Read/Write)"},
    {1327, 580, "Segment 3 (Heap - Read/Write)"},
    {1952, 96, "Segment 4 (Shared Library)"}
};

void translate(int seg, int offset) {
    if (seg < 0 || seg >= 5) {
        printf("Logical Address (Seg %d, Offset %d) -> TRAP: Invalid Segment\n", seg, offset);
        return;
    }
    if (offset >= seg_table[seg].limit) {
        printf("Logical Address (Seg %d, Offset %d) -> TRAP: Segmentation Fault (Offset %d >= Limit %d)\n",
               seg, offset, offset, seg_table[seg].limit);
    } else {
        printf("Logical Address (Seg %d, Offset %d) [%s] -> Physical Address: %d\n",
               seg, offset, seg_table[seg].name, seg_table[seg].base + offset);
    }
}

int main(void) {
    printf("=== Segmentation Address Translation Demonstration ===\n");
    translate(0, 430);  /* Valid Code */
    translate(1, 10);   /* Valid Data */
    translate(1, 20);   /* Trap: Offset > Limit */
    translate(2, 50);   /* Valid Stack */
    translate(3, 400);  /* Valid Heap */
    translate(4, 95);   /* Valid Shared */
    translate(4, 100);  /* Trap: Offset > Limit */
    translate(5, 10);   /* Trap: Invalid Segment */
    return 0;
}
