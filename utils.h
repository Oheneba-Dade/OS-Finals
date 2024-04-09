#ifndef UTILS_H
#define UTILS_H

#include <limits.h>
#include "segments.h"

#define MAX_SEGMENTS 4
#define MAX_OFFSET 100
#define PHYSICAL_MEMORY_SIZE 1024
#define MAX_NUM_FREE_SEGMENTS 512 

typedef struct{
    int segment_number;
    int offset;
} LogicalAddress;

LogicalAddress generate_random_logical_address();
int* bestFit(SegmentEntry freeSegments[], int segmentSize);
SegmentEntry* findFreeSegments(int physicalMemory[]);
int getFileSize(char *filename);

#endif // UTILS_H