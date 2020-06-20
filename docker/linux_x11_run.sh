#!/bin/bash

export DISPLAY=$(awk '/nameserver / {print $2; exit}' /etc/resolv.conf 2>/dev/null):0
/mnt/c/Users/niels/Projects/VSCode-docker-IDE/bin/run_linux