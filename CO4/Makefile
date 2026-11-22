CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

all: Task02/file_allocation Task04/disk_scheduling Task04/disk_sim_10k Task06/streaming_sim

Task02/file_allocation: Task02/file_allocation.c
	$(CC) $(CFLAGS) $< -o $@

Task04/disk_scheduling: Task04/disk_scheduling.c
	$(CC) $(CFLAGS) $< -o $@

Task04/disk_sim_10k: Task04/disk_sim_10k.c
	$(CC) $(CFLAGS) $< -o $@

Task06/streaming_sim: Task06/streaming_sim.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f Task02/file_allocation Task04/disk_scheduling Task04/disk_sim_10k Task06/streaming_sim
