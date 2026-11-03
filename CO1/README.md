# CSA0413 - Operating Systems: Assignment 1 (CO1)
**Title:** Evaluate and Justify the Operating-System Design of a Smart Hospital (Total Marks - 50)  
**Student Name:** M.V. Rakesh Reddy  
**Register Number:** 19524164  
**Department:** Artificial Intelligence and Data Science (AI & DS)  
**Course & Code:** Operating Systems (CSA0413)  
**Course Faculty:** Kruthika K  
**Submission Date:** 04-11-2026  
**Compiler & Version:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0`  
**Linux Distribution & Kernel:** Debian 12 (Bookworm) / Linux 6.12.105+ x86_64  
**Exact Compilation Command:** `gcc -std=c11 -Wall -Wextra -pthread -O2`  
**GitHub Repository Link:** https://github.com/Rakeshreddymeruva/CSA0413-OS/tree/main/CO1  

---

## Directory Structure
```
CO1/
├── Makefile
├── README.md
├── Task06/
│   └── copy_file.c
├── Task07/
│   ├── buffering_experiment.c
│   └── shell_jobs.c
└── Task10/
    └── process_vs_thread.c
```

---

## Compilation & Execution Instructions
```bash
# Inside the CO1 directory:
make

# Execute Task 6: System call cost with varying buffer sizes
./Task06/copy_file

# Execute Task 7: Process control (fork, exec, wait)
./Task07/shell_jobs

# Execute Task 7 Buffering Experiment (redirected to file)
./Task07/buffering_experiment > test_out.txt
cat test_out.txt

# Execute Task 10: Process vs. Thread benchmark
./Task10/process_vs_thread
```

---

## Verified Execution Outputs

### Task 6: `copy_file.c` Output
```
buffer    1 bytes: 10001 read() calls
buffer  512 bytes:    21 read() calls
buffer 4096 bytes:     4 read() calls
```

### Task 7: `shell_jobs.c` Output
```
shell: running job 1
42
job 1 exit status 0
shell: running job 2
job 2 exit status 3
```

### Task 10: `process_vs_thread.c` Output
```
1,000 Processes: 0.1440 s (143.95 us/proc)
1,000 Threads:   0.0238 s (23.77 us/thread)
Speedup Ratio:   6.06x faster
```
