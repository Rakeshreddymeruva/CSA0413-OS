#include <stdio.h>
#include <string.h>

int main(void) {
    const char *filename = "server.log";
    const char *pattern = "ERROR";
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[512];
    int line_no = 0, matches = 0;

    printf("GREP Simulation: Searching \"%s\" in \"%s\"\n\n", pattern, filename);
    while (fgets(line, sizeof(line), fp)) {
        line_no++;
        if (strstr(line, pattern) != NULL) {
            matches++;
            printf("Line %d: %s", line_no, line);
            if (line[strlen(line) - 1] != '\n') printf("\n");
        }
    }
    fclose(fp);
    printf("\nTotal lines scanned: %d | Matching lines: %d\n", line_no, matches);
    return 0;
}
