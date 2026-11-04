CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

all: Q1/libencrypt.so Q1/banking_app_static Q1/banking_app_dynamic Q1/banking_app_dlopen Q2/paging_simulation Q3/segmentation_sim Q4/demand_paging_sim Q5/page_replacement Q7/realtime_mlock

Q1/libencrypt.so: Q1/encrypt_lib.c
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@

Q1/banking_app_static: Q1/banking_app.c Q1/encrypt_lib.c
	$(CC) $(CFLAGS) -static $^ -o $@

Q1/banking_app_dynamic: Q1/banking_app.c Q1/libencrypt.so
	$(CC) $(CFLAGS) -L./Q1 -Wl,-rpath=./Q1 -Wl,-rpath='$$ORIGIN' $< -lencrypt -o $@

Q1/banking_app_dlopen: Q1/banking_app_dlopen.c
	$(CC) $(CFLAGS) -ldl $< -o $@

Q2/paging_simulation: Q2/paging_simulation.c
	$(CC) $(CFLAGS) $< -o $@

Q3/segmentation_sim: Q3/segmentation_sim.c
	$(CC) $(CFLAGS) $< -o $@

Q4/demand_paging_sim: Q4/demand_paging_sim.c
	$(CC) $(CFLAGS) $< -o $@

Q5/page_replacement: Q5/page_replacement.c
	$(CC) $(CFLAGS) $< -o $@

Q7/realtime_mlock: Q7/realtime_mlock.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f Q1/*.so Q1/banking_app_* Q2/paging_simulation Q3/segmentation_sim Q4/demand_paging_sim Q5/page_replacement Q7/realtime_mlock
