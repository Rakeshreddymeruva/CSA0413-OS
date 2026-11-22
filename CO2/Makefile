CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pthread -O2

all: Q1/process_states Q2/round_robin Q3/traffic_threads Q4/pipe_weather Q5/bounded_buffer Q6/banker_algorithm

Q1/process_states: Q1/process_states.c
	$(CC) $(CFLAGS) $< -o $@

Q2/round_robin: Q2/round_robin.c
	$(CC) $(CFLAGS) $< -o $@

Q3/traffic_threads: Q3/traffic_threads.c
	$(CC) $(CFLAGS) $< -o $@

Q4/pipe_weather: Q4/pipe_weather.c
	$(CC) $(CFLAGS) $< -o $@

Q5/bounded_buffer: Q5/bounded_buffer.c
	$(CC) $(CFLAGS) $< -o $@

Q6/banker_algorithm: Q6/banker_algorithm.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f Q1/process_states Q2/round_robin Q3/traffic_threads Q4/pipe_weather Q5/bounded_buffer Q6/banker_algorithm
