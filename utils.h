#ifndef UTILS_H
#define UTILS_H

#include <limits.h>
#include "segments.h"

#define MAX_SEGMENTS 3
#define MAX_OFFSET 100
#define PHYSICAL_MEMORY_SIZE 1024
#define MAX_NUM_FREE_SEGMENTS 512 

typedef struct{
    int segment_number;
    int offset;
} LogicalAddress;

typedef struct {
    SegmentEntry* freeSegmentsPointer;
    int size;
} FreeSegmentsAndSize;

LogicalAddress generate_random_logical_address();
int bestFit(SegmentEntry freeSegments[], int numFreeSegments, int segmentSize);
FreeSegmentsAndSize findFreeSegments(int physicalMemory[]);
int getFileSize(char *filename);
void randomly_assign_segments(int memory[], int num_segments, int segment_size);


#endif // UTILS_H