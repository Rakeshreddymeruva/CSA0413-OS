#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int emp_id;
    char name[32];
    float salary;
} Employee;

int main(void) {
    const char *filename = "employees.dat";
    FILE *fp = fopen(filename, "w+b");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    Employee initial[5] = {
        {1, "Aarav Sharma", 45000.0f},
        {2, "Priya Nair", 52000.0f},
        {3, "Rakesh Reddy", 48000.0f},
        {4, "Sneha Iyer", 61000.0f},
        {5, "Vikram Rao", 55000.0f}
    };

    fwrite(initial, sizeof(Employee), 5, fp);
    fflush(fp);

    printf("Initial 5 Employee Records (Record Size = %zu bytes):\n", sizeof(Employee));
    rewind(fp);
    Employee e;
    for (int i = 0; i < 5; i++) {
        fread(&e, sizeof(Employee), 1, fp);
        printf("  EmpID: %d | Name: %-15s | Salary: %.2f\n", e.emp_id, e.name, e.salary);
    }

    // Directly seek to EmpID = 3 (0-based index 2)
    int target_id = 3;
    long offset = (long)(target_id - 1) * sizeof(Employee);
    fseek(fp, offset, SEEK_SET);
    fread(&e, sizeof(Employee), 1, fp);
    printf("\nDirect Read at offset %ld bytes (EmpID = %d):\n", offset, target_id);
    printf("  Before Update -> EmpID: %d | Name: %s | Salary: %.2f\n", e.emp_id, e.name, e.salary);

    // Update Salary directly without touching other records
    e.salary = 65000.0f;
    fseek(fp, offset, SEEK_SET);
    fwrite(&e, sizeof(Employee), 1, fp);
    fflush(fp);

    printf("\nUpdated EmpID = %d Salary to %.2f directly in-place.\n", target_id, e.salary);
    printf("\nAll Records After Direct Random-Access Update:\n");
    rewind(fp);
    for (int i = 0; i < 5; i++) {
        fread(&e, sizeof(Employee), 1, fp);
        printf("  EmpID: %d | Name: %-15s | Salary: %.2f\n", e.emp_id, e.name, e.salary);
    }

    fclose(fp);
    return 0;
}
