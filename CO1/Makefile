CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pthread -O2

all: Task06/copy_file Task07/shell_jobs Task07/buffering_experiment Task10/process_vs_thread

Task06/copy_file: Task06/copy_file.c
	$(CC) $(CFLAGS) $< -o $@

Task07/shell_jobs: Task07/shell_jobs.c
	$(CC) $(CFLAGS) $< -o $@

Task07/buffering_experiment: Task07/buffering_experiment.c
	$(CC) $(CFLAGS) $< -o $@

Task10/process_vs_thread: Task10/process_vs_thread.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f Task06/copy_file Task07/shell_jobs Task07/buffering_experiment Task10/process_vs_thread *.dat *.txt
