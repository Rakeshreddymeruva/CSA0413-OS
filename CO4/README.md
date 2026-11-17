# CSA0413 - Operating Systems: Assignment 4 (CO4)
**Title:** Optimising File Storage and Disk Access (Total Marks - 50)  
**Student Name:** M.V. Rakesh Reddy  
**Register Number:** 19524164  
**Department:** Artificial Intelligence and Data Science (AI & DS)  
**Course & Code:** Operating Systems (CSA0413)  
**Course Faculty:** Kruthika K  
**Submission Date:** 17-11-2026  
**Compiler & Version:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0`  
**Linux Distribution & Kernel:** Debian 12 (Bookworm) / Linux 6.12.105+ x86_64  
**Exact Compilation Command:** `gcc -std=c11 -Wall -Wextra -O2`  
**GitHub Repository Link:** https://github.com/Rakeshreddymeruva/CSA0413-OS/tree/main/CO4  

---

## Directory Structure
```
CO4/
├── Makefile
├── README.md
├── Task01/
├── Task02/
│   └── file_allocation.c
├── Task03/
│   └── inspect_fs.sh
├── Task04/
│   ├── disk_scheduling.c
│   └── disk_sim_10k.c
├── Task05/
└── Task06/
    └── streaming_sim.c
```

---

## Compilation & Execution Instructions
```bash
# Inside the CO4 directory:
make

# Execute Task 2: Contiguous (First-Fit) vs Indexed File Allocation
./Task02/file_allocation

# Execute Task 3: Real Linux Filesystem Inspection (stat, df -i, ls -li)
bash Task03/inspect_fs.sh

# Execute Task 4: Disk Scheduling (FCFS, SSTF, SCAN, C-SCAN)
./Task04/disk_scheduling

# Execute Task 4: 10,000-Request Load Simulation & SSTF Starvation Test
./Task04/disk_sim_10k

# Execute Task 6: Video-Streaming Storage Design Simulation
./Task06/streaming_sim
```

---

## Verified Execution Outputs

### Task 2: `file_allocation.c` Output
```
AAAAAA........CCCCC.............
E (10 blocks) contiguous: start 19
E (10 blocks) indexed: index block 6, data blocks 7 8 9 10 11 12 13 29 30 31
AAAAAAeEEEEEEECCCCCEEEEEEEEEEEEE
```

### Task 4: `disk_scheduling.c` Output
```
FCFS   53 98 183 37 122 14 124 65 67 -> 640 cylinders
SSTF   53 65 67 37 14 98 122 124 183 -> 236 cylinders
SCAN   53 37 14 0 65 67 98 122 124 183 -> 236 cylinders
C-SCAN 53 ... 199, jump to 0 ... 37 -> 183 cylinders (+199 for the jump)
```

### Task 6: `streaming_sim.c` Output
```
Design A (NVMe Hot Cache + RAID-10 HDD + 64KB + LOOK): Avg Startup Latency = 0.647 ms (1546 req/s/node)
Design B (Uncached HDD + 4KB + FCFS):                  Avg Startup Latency = 8.495 ms (118 req/s/node)
Speedup (Design A over Design B): 13.13x lower latency
```
