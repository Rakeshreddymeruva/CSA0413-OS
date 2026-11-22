# CSA0413 - Operating Systems: Assignment 2 (CO2)
**Title:** Process Management, CPU Scheduling, Threads, IPC, Synchronisation & Deadlock Handling (Total Marks - 50)  
**Student Name:** M.V. Rakesh Reddy  
**Register Number:** 19524164  
**Department:** Artificial Intelligence and Data Science (AI & DS)  
**Course & Code:** Operating Systems (CSA0413)  
**Course Faculty:** Kruthika K  
**Submission Date:** 04-11-2026  
**Compiler & Version:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0`  
**Linux Distribution & Kernel:** Debian 12 (Bookworm) / Linux 6.12.105+ x86_64  
**Exact Compilation Command:** `gcc -std=c11 -Wall -Wextra -pthread -O2`  
**GitHub Repository Link:** https://github.com/Rakeshreddymeruva/CSA0413-OS/tree/main/CO2  

---

## Directory Structure
```
CO2/
├── Makefile
├── README.md
├── Q1/
│   └── process_states.c
├── Q2/
│   └── round_robin.c
├── Q3/
│   └── traffic_threads.c
├── Q4/
│   └── pipe_weather.c
├── Q5/
│   └── bounded_buffer.c
└── Q6/
    └── banker_algorithm.c
```

---

## Compilation & Execution Instructions
```bash
# Inside the CO2 directory:
make

# Execute Q1: Process creation & inspection
./Q1/process_states

# Execute Q2: Round Robin CPU Scheduling
./Q2/round_robin

# Execute Q3: POSIX threads camera processing & race conditions
./Q3/traffic_threads

# Execute Q4: Weather station sensor pipe IPC
./Q4/pipe_weather

# Execute Q5: Bounded-buffer synchronization (semaphores + mutex)
./Q5/bounded_buffer

# Execute Q6: Dijkstra's Banker's Deadlock Avoidance Algorithm
./Q6/banker_algorithm
```

---

## Verified Execution Outputs

### Q2: `round_robin.c` Output
```
Gantt: P1(0-3) P2(3-6) P3(6-9) P4(9-12) P1(12-15) P2(15-16) P3(16-19) P4(19-21) P1(21-23) P3(23-26)
Process TAT WT
P1        23  15
P2        15  11
P3        24  15
P4        18  13
Average TAT = 20.00, average WT = 13.50
```

### Q3: `traffic_threads.c` Output
```
Processing 64 cameras (64000 frames total)...
Pool Size  1: Time = 0.0012s, Speedup = 1.00x | Protected = 64000 (Expected 64000), Unprotected = 64000
Pool Size  4: Time = 0.0056s, Speedup = 0.22x | Protected = 64000 (Expected 64000), Unprotected = 63424
Pool Size  8: Time = 0.0058s, Speedup = 0.21x | Protected = 64000 (Expected 64000), Unprotected = 63261
Pool Size 16: Time = 0.0056s, Speedup = 0.22x | Protected = 64000 (Expected 64000), Unprotected = 62986
```

### Q4: `pipe_weather.c` Output
```
analyser: 6 readings, average 35.5, max 41
reader: done
```

### Q5: `bounded_buffer.c` Output
```
items consumed: 20, sum = 210 (expected 210)
```

### Q6: `banker_algorithm.c` Output
```
initial state safe: P1 P3 P4 P0 P2
P1 request: granted, safe sequence P1 P3 P4 P0 P2
P4 request: must wait (not available)
P0 request: denied (unsafe)
```
