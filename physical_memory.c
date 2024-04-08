#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "segments.h"

/**
 * The function `initializeMemory` allocates memory of a specified size and initializes it with zeros.
 * 
 * @param memorySize The `memorySize` parameter in the `initializeMemory` function represents the
 * number of integer elements that you want to allocate memory for. This parameter specifies the size
 * of the memory block that will be allocated dynamically using `malloc`.
 * 
 * @return The function `initializeMemory` is returning a pointer to an array of integers, which
 * represents the initialized physical memory.
 */
int* initializeMemory(int memorySize) {
    int* physicalMemory = malloc(memorySize * sizeof(int));
    for (int i = 0; i < memorySize; i++) {
        physicalMemory[i] = 0; //0 represents empty
    }
    return physicalMemory;
}

/**
 * The function `fillMemory` fills a portion of physical memory with the value 1 starting from a
 * specified index.
 * 
 * @param physicalMemory The `physicalMemory` parameter is a pointer to an integer array representing
 * the physical memory. This function `fillMemory` will fill a portion of this memory with the value
 * `1` to indicate that it is filled.
 * @param start The `start` parameter indicates the starting index in the `physicalMemory` array where
 * the filling operation should begin.
 * @param size The `size` parameter in the `fillMemory` function represents the number of elements in
 * the `physicalMemory` array that need to be filled with the value `1`.
 */
void fillMemory(int* physicalMemory, int start, int size) {
    for (int i = start; i < start+size; i++) {
        physicalMemory[i] = 1; //1 represents filled
    }
}

/**
 * The above type defines a structure for managing free memory blocks in a segment with a specified
 * capacity.
 * @property {SegmentEntry} freeBlocks - `freeBlocks` is a pointer to a `SegmentEntry` type, which
 *  represents a list or array of free memory blocks.
 * @property {int} capacity - The `capacity` property in the `freeMemory` struct represents the total
 * number of elements that can be stored in the `freeBlocks` array.
 */
typedef struct {
    int capacity;
    SegmentEntry freeBlocks[1024];
} freeMemory;

