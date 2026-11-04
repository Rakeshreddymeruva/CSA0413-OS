#!/usr/bin/env python3
# RAID Capacity & Failure Probability Calculations for 6 Disks of 4 TB each
disks = 6
disk_cap_tb = 4.0
raw_capacity = disks * disk_cap_tb

print(f"=== RAID Capacity & Fault Tolerance Analysis ({disks} Disks of {disk_cap_tb} TB) ===")
print(f"Total Raw Capacity: {raw_capacity} TB\n")

raids = {
    "RAID 0": {"usable": disks * disk_cap_tb, "fault_tol": 0, "overhead": "0%"},
    "RAID 1": {"usable": (disks / 2) * disk_cap_tb, "fault_tol": 1, "overhead": "50%"},
    "RAID 5": {"usable": (disks - 1) * disk_cap_tb, "fault_tol": 1, "overhead": "16.7%"},
    "RAID 6": {"usable": (disks - 2) * disk_cap_tb, "fault_tol": 2, "overhead": "33.3%"},
    "RAID 10": {"usable": (disks / 2) * disk_cap_tb, "fault_tol": 1, "overhead": "50%"}
}

for name, data in raids.items():
    print(f"{name:7s}: Usable = {data['usable']:4.1f} TB ({data['usable']/raw_capacity*100:4.1f}%) | Fault Tolerance = {data['fault_tol']} disk(s) | Capacity Overhead = {data['overhead']}")
