#ifndef OS_FINALS_PHYSICAL_MEMORY_H
#define OS_FINALS_PHYSICAL_MEMORY_H
#include "segments.h"

typedef struct {
    int capacity;
    SegmentEntry freeBlocks[1024];
} freeMemory;

int* initializeMemory(int memorySize);
void fillMemory(int physicalMemory[], int start, int size);
void printMemory(int physicalMemory[], int memorySize);

#endif //OS_FINALS_PHYSICAL_MEMORY_H 
