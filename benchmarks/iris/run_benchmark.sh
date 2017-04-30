#!/bin/bash
RUNS=5
TIME_COMMAND="gtime"

# real,user,sys,total memory
TIME_FLAGS='-f %e\t%U\t%S\t%M'

# parameters:
# 1 : datatype
# 2 : program
benchmark () {
    for I in `seq 1 ${RUNS}`;
    do
        OUTPUT=$(${TIME_COMMAND} ${TIME_FLAGS} ${2} 2>&1)
        IFS=$'\n' read -rd '' -a DATA <<<"${OUTPUT}"
        ERROR_RATE=$(echo ${OUTPUT} | cut -d' ' -f4 | tr -d '%')
        REAL=$(echo ${OUTPUT} | cut -d' ' -f5)
        USER=$(echo ${OUTPUT} | cut -d' ' -f6)
        SYS=$(echo ${OUTPUT} | cut -d' ' -f7)
        MEM=$(echo ${OUTPUT} | cut -d' ' -f8)

        echo "${1},${ERROR_RATE},${REAL},${USER},${SYS},${MEM}"
    done
}

# print csv header
echo "datatype,error.rate,real,user,system,max.memory"

benchmark "double" "./iris_double"
benchmark "float" "./iris_float"
benchmark "fix16" "./iris_fix16"
