#!/bin/bash
PROGRAM=./iris
RUNS=5
TIME_COMMAND="gtime"

# real,user,sys,total memory
TIME_FLAGS='-f %e\t%U\t%S\t%M'

# print csv header
echo "error.rate,real,user,system,max.memory"

for I in `seq 1 ${RUNS}`;
do
    OUTPUT=$(${TIME_COMMAND} ${TIME_FLAGS} ${PROGRAM} 2>&1)
    IFS=$'\n' read -rd '' -a DATA <<<"${OUTPUT}"
    ERROR_RATE=$(echo ${OUTPUT} | cut -d' ' -f4 | tr -d '%')
    REAL=$(echo ${OUTPUT} | cut -d' ' -f5)
    USER=$(echo ${OUTPUT} | cut -d' ' -f6)
    SYS=$(echo ${OUTPUT} | cut -d' ' -f7)
    MEM=$(echo ${OUTPUT} | cut -d' ' -f8)

    echo "${ERROR_RATE},${REAL},${USER},${SYS},${MEM}"
done
