# !/bin/sh
kill -9 $(ps -o pid,comm | grep -i k1160 | awk '{print $1}')
