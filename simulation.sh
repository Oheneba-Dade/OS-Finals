#!/bin/bash

gcc -o simulation physical_memory.c segments.c simulation.c utils.c process.c
./simulation