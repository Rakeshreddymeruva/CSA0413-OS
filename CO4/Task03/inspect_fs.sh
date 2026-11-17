#!/usr/bin/env bash
set -euo pipefail
echo "=== 1. File Metadata & Block Size (stat) ==="
stat Task02/file_allocation.c
echo ""
echo "=== 2. Inode Usage (df -i) ==="
df -i .
echo ""
echo "=== 3. Directory Inode Listing (ls -li) ==="
ls -li Task02/
