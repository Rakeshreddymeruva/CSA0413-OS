#!/usr/bin/env bash
set -euo pipefail
THRESHOLD=80
USAGE=$(df -P /working_dir | awk 'NR==2 {gsub("%",""); print $5}')
if [ "$USAGE" -ge "$THRESHOLD" ]; then
    echo "ALERT: Disk usage at ${USAGE}% (threshold ${THRESHOLD}%)"
else
    echo "OK: Disk usage at ${USAGE}% (below ${THRESHOLD}%)"
fi
