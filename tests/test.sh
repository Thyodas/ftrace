#!/bin/bash

gcc ./tests/m32.c -o m32
./ftrace -s ./m32 &> out &
sleep 1
pid=$(pidof ./m32)
cat "/proc/${pid}/maps"
objdump -M intel -d ./m32 > m32.asm
objdump -fs ./m32 > m32_objdump
readelf -r ./m32 > m32_readelf
cat m32.asm
cat m32_objdump
cat m32_readelf
wait
cat out
