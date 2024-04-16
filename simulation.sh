#!/bin/bash

# Compile the code
gcc -o simulation simulation.c utils.c process.c segments.c physical_memory.c -lm

# checks if the programs compiled successfully
if [ $? -ne 0 ]; then
	echo "Compilation failed"
	exit 1
fi

# Run the simulation with different number of processes
<<<<<<< HEAD
for i in {1..1}
=======
for i in {1..2}
>>>>>>> dd906be92df4f6af3d62898e33b0a08a163fbf3a
do
   echo "Running simulation with $i processes"
   ./simulation $i
   echo "Finished simulating with $i processes"
done