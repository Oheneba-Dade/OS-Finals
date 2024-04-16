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
 * @param physicalMemory The `physicalMemory` parameter is an array that represents the physical
 * memory. The function `fillMemory` will fill a portion of this physical memory with the value 1 to
 * indicate that it is filled.
 * @param start The `start` parameter in the `fillMemory` function represents the starting index in the
 * `physicalMemory` array where the filling operation will begin.
 * @param size The `size` parameter in the `fillMemory` function represents the number of elements in
 * the `physicalMemory` array that need to be filled with the value `1`.
 */
void fillMemory(int physicalMemory[], int start, int size) {
    printf("Filling memory from %d\n\n", start);
    for (int i = start; i < start+size; i++) {
        physicalMemory[i] = 1; //1 represents filled
    }
}

/** 
 * @param physicalMemory The `physicalMemory` parameter is an array that represents the physical
 * memory. It is an array of integers where each element corresponds to a memory location. 
 * @param start The `start` parameter represents the starting index in the `physicalMemory` array from
 * which memory deallocation should begin.
 * @param size The `size` parameter in the `deallocateMemory` function represents the number of memory
 * slots that need to be deallocated starting from the `start` index in the `physicalMemory` array.
 */
void deallocateMemory(int physicalMemory[], int start, int size) {
    printf("Deallocating memory from %d\n\n", start);
    for (int i = start; i < start+size; i++) {
        physicalMemory[i] = 0; //0 represents empty
    }
}

/**
 * The function `printMemory` prints the contents of an array representing physical memory.
 * 
 * @param physicalMemory The `physicalMemory` parameter is an array that represents the physical
 * memory. The function `printMemory` will print the contents of this physical memory array to the
 * console.
 * @param memorySize The `memorySize` parameter in the `printMemory` function represents the size of
 * the `physicalMemory` array.
 */
void printMemory(int physicalMemory[], int memorySize) {
    printf("Memory content:\n");
    for (int i = 0; i < memorySize; i++) {
        printf("%d ", physicalMemory[i]);

        // Print a new line after every 32 elements
        if ((i + 1) % 64 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

//void deallocateMemory();