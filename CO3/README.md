# CSA0413 - Operating Systems: Assignment 3 (CO3)
**Title:** Memory-Management Mechanisms: Linking, Paging, Segmentation, Demand Paging, Page Replacement & Disk Storage (Total Marks - 50)  
**Student Name:** M.V. Rakesh Reddy  
**Register Number:** 19524164  
**Department:** Artificial Intelligence and Data Science (AI & DS)  
**Course & Code:** Operating Systems (CSA0413)  
**Course Faculty:** Kruthika K  
**Submission Date:** 04-11-2026  
**Compiler & Version:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0`  
**Linux Distribution & Kernel:** Debian 12 (Bookworm) / Linux 6.12.105+ x86_64  
**Exact Compilation Command:** `gcc -std=c11 -Wall -Wextra -O2`  
**GitHub Repository Link:** https://github.com/Rakeshreddymeruva/CSA0413-OS/tree/main/CO3  

---

## Directory Structure
```
CO3/
├── Makefile
├── README.md
├── Q1/
│   ├── banking_app.c
│   ├── banking_app_dlopen.c
│   ├── encrypt_lib.c
│   └── encrypt_lib.h
├── Q2/
│   └── paging_simulation.c
├── Q3/
│   └── segmentation_sim.c
├── Q4/
│   └── demand_paging_sim.c
├── Q5/
│   └── page_replacement.c
├── Q6/
│   └── raid_calc.py
└── Q7/
    └── realtime_mlock.c
```

---

## Compilation & Execution Instructions
```bash
# Inside the CO3 directory:
make

# Execute Q1: Static vs Dynamic Linking & Runtime dlopen()
./Q1/banking_app_static
./Q1/banking_app_dynamic
./Q1/banking_app_dlopen

# Execute Q2: Paging Address Translation Simulation
./Q2/paging_simulation

# Execute Q3: Segmentation Translation and Limit Trap Verification
./Q3/segmentation_sim

# Execute Q4: Demand Paging Memory Locality Simulator
./Q4/demand_paging_sim

# Execute Q5: Page Replacement Algorithms (FIFO, LRU, Optimal, Belady)
./Q5/page_replacement

# Execute Q6: RAID 0, 1, 5, 6, 10 Capacity & Fault Tolerance Analysis
python3 Q6/raid_calc.py

# Execute Q7: Real-Time Memory Locking via mlock()
./Q7/realtime_mlock
```

---

## Verified Execution Outputs

### Q1: Linking & Loading Verification
- Static Binary Size: **762 KB** (`banking_app_static`)
- Dynamic Binary Size: **16 KB** (`banking_app_dynamic`) — **47x reduction**
- `dlopen()` dynamically resolves `encrypt_data` symbol at runtime without static link dependencies.

### Q2: `paging_simulation.c` Output
```
   0 -> page 0 offset    0 : physical 5120
1500 -> page 1 offset  476 : physical 2524
3100 -> page 3 offset   28 : physical 7196
6200 -> page 6 offset   56 : physical 3128
9000 -> page 8 offset  808 : invalid address
2049 -> page 2 offset    1 : page fault
```

### Q3: `segmentation_sim.c` Output
```
Logical Address (Seg 0, Offset 430) [Segment 0 (Code - Read Only)] -> Physical Address: 649
Logical Address (Seg 1, Offset 10) [Segment 1 (Data - Read/Write)] -> Physical Address: 2310
Logical Address (Seg 1, Offset 20) -> TRAP: Segmentation Fault (Offset 20 >= Limit 14)
Logical Address (Seg 2, Offset 50) [Segment 2 (Stack - Read/Write)] -> Physical Address: 140
Logical Address (Seg 3, Offset 400) [Segment 3 (Heap - Read/Write)] -> Physical Address: 1727
Logical Address (Seg 4, Offset 95) [Segment 4 (Shared Library)] -> Physical Address: 2047
Logical Address (Seg 4, Offset 100) -> TRAP: Segmentation Fault (Offset 100 >= Limit 96)
Logical Address (Seg 5, Offset 10) -> TRAP: Invalid Segment
```

### Q5: `page_replacement.c` Output
```
3 frames: FIFO 15, LRU 12, Optimal 9
4 frames: FIFO 10, LRU 8, Optimal 8
Belady string, FIFO: 3 frames 9 faults, 4 frames 10 faults
```

### Q6: RAID Calculations Output (6 Disks of 4 TB)
```
RAID 0 : Usable = 24.0 TB (100.0%) | Fault Tolerance = 0 disk(s)
RAID 1 : Usable = 12.0 TB (50.0%)  | Fault Tolerance = 1 disk(s)
RAID 5 : Usable = 20.0 TB (83.3%)  | Fault Tolerance = 1 disk(s)
RAID 6 : Usable = 16.0 TB (66.7%)  | Fault Tolerance = 2 disk(s)
RAID 10: Usable = 12.0 TB (50.0%)  | Fault Tolerance = 1 disk(s)
```

### Q7: `realtime_mlock.c` Output
```
Measuring memory access WITHOUT mlock...
Unlocked loop execution time: 420.33 us
Locking memory frames via mlock()...
Memory frames locked into physical RAM successfully.
Locked loop execution time:   126.75 us
```
