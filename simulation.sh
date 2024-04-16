#!/bin/bash

# Compile the code
gcc -o simulation simulation.c utils.c process.c segments.c physical_memory.c -lm

# checks if the programs compiled successfully
if [ $? -ne 0 ]; then
	echo "Compilation failed"
	exit 1
fi

# Run the simulation with different number of processes
for i in 9;
do
   echo "Running simulation with $i processes"
   ./simulation $i
   echo "Finished simulating with $i processes"
done