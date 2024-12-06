#!/bin/bash



# Check if argument is provided
if [ "$#" -ne 1 ]; then
    echo "Uso: $0 <sistemaLinear.dat>"
    exit 1
fi

# Assign arguments to variables
sl=$1

# Check if linear system file exists
if [ ! -f "$sl" ]; then
    echo "Arquivo do sistema linear $sl não encontrado."
    exit 1
fi

METRICA="FLOPS_DP"
CPU=1

#Gerar a saída do programa sem likwid
./perfSL < $sl

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for k in $METRICA
do
    > ${k}.log
    likwid-perfctr -C ${CPU} -g ${k} -m ./perfSL < $sl >> ${k}.log
done

for k in $METRICA
do
    echo "Saída LIKWID ${k}:"
    awk '
        /Region/ && !/Region Info/ {region=$0; sub(/.*Region /, "", region); sub(/, Group.*/, "", region);} 
        /DP MFLOP\/s/ && !/AVX/ {print region ": " $5 " MFLOP/s"}
    ' "${k}.log"
    echo
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
