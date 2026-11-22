#include <stdio.h>
#include <stdlib.h>

/* Simulates serving 10,000 video playback/seek requests across two storage designs:
   Design A: Tiered NVMe SSD cache (80% hit rate, 0.05 ms) + RAID-10 HDD (64 KB blocks, LOOK)
   Design B: Uncached HDD (100% disk, 4 KB blocks, FCFS)
*/
int main(void) {
    srand(101);
    const int REQUESTS = 10000;
    double total_latency_A = 0.0, total_latency_B = 0.0;
    int head_A = 100, head_B = 100;

    for (int i = 0; i < REQUESTS; i++) {
        int is_hot = (rand() % 100) < 80; /* 80% first-week lecture views */
        int cyl = rand() % 200;

        /* Design A: SSD cache hit = 0.05 ms, miss = RAID-10 HDD seek + 64KB transfer */
        if (is_hot) {
            total_latency_A += 0.05;
        } else {
            int seek_cyl = abs(cyl - head_A) / 4; /* LOOK + RAID10 locality */
            head_A = cyl;
            total_latency_A += 2.0 + seek_cyl * 0.04 + 0.4; /* ms */
        }

        /* Design B: Uncached HDD with FCFS and 4KB blocks (16x more seeks for 64KB chunk) */
        int seek_cyl_B = abs(cyl - head_B);
        head_B = cyl;
        total_latency_B += 4.5 + seek_cyl_B * 0.06; /* ms */
    }

    double avg_A = total_latency_A / REQUESTS;
    double avg_B = total_latency_B / REQUESTS;
    printf("=== Video-Streaming Storage Workload Simulation (%d Requests) ===\n", REQUESTS);
    printf("Design A (NVMe Hot Cache + RAID-10 HDD + 64KB + LOOK): Avg Startup Latency = %.3f ms (%.0f req/s/node)\n",
           avg_A, 1000.0 / avg_A);
    printf("Design B (Uncached HDD + 4KB + FCFS):                  Avg Startup Latency = %.3f ms (%.0f req/s/node)\n",
           avg_B, 1000.0 / avg_B);
    printf("Speedup (Design A over Design B): %.2fx lower latency\n", avg_B / avg_A);
    return 0;
}
