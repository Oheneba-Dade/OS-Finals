#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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


LogicalAddress generate_random_logical_address(){
    LogicalAddress address;

     // Generate a random number within the inclusive range
    address.segment_number = (rand() % (MAX_SEGMENTS+ 1));
    address.offset =  (rand() % (MAX_OFFSET + 1));
    return address;

}


/**
 * @param freeSegments The `freeSegments` parameter in the `bestFit` function is an array of
 * `SegmentEntry` structures representing the free memory segments available for allocation.
 * @param segmentSize The `segmentSize` parameter in the `bestFit` function represents the size of the
 * segment that needs to be allocated. This function is designed to find the best fit for the given
 * segment size among the free segments available in the `freeSegments` array.
 * @return The function `bestFit` is returning an array of two integers. The first integer
 * in the array represents the base number of the best fit segment found, and the second integer
 * represents the size of that segment.
 */
int* bestFit(SegmentEntry freeSegments[], int segmentSize) {
    int numFreeSegments = sizeof(freeSegments) / sizeof(freeSegments[0]);
    int bestFitBaseAndSize[2];
    bestFitBaseAndSize[0] = -1; // Default value indicating no best fit found
    bestFitBaseAndSize[1] = INT_MAX; // Set to maximum possible value initially
    for (int i = 0; i < numFreeSegments; i++) {
        if (segmentSize <= freeSegments[i].size) {
            int difference = freeSegments[i].size - segmentSize;
            if (difference < bestFitBaseAndSize[1]) {
                bestFitBaseAndSize[0] = freeSegments[i].baseNumber;
                bestFitBaseAndSize[1] = freeSegments[i].size;
            }
        }
    }
    return bestFitBaseAndSize;
}


/**
 * @param physicalMemory An array that represents the physical memory
 * @return The function `findFreeSegments` returns a pointer to an array of `SegmentEntry` structures
 * representing the free segments in the `physicalMemory` array.
 */
SegmentEntry* findFreeSegments(int physicalMemory[]) {
     SegmentEntry* freeSegments = malloc(MAX_NUM_FREE_SEGMENTS * sizeof(SegmentEntry));
    int freeSegmentsIndex = 0;
    int segmentStartIndex = -1;

    for (int i = 0; i < PHYSICAL_MEMORY_SIZE; i++) {
        if (physicalMemory[i] == 0) {
            if (segmentStartIndex == -1) {
                segmentStartIndex = i;
            }
        } else {
            if (segmentStartIndex != -1) {
                    SegmentEntry segment;
                    segment.baseNumber = segmentStartIndex;
                    segment.size = i - segmentStartIndex;
                    //printf("Free segment: base=%d, size=%d\n", segment.baseNumber, segment.size); //was wondering if we should be printing the free spaces to make the simulation nicer
                    freeSegments[freeSegmentsIndex++] = segment;
                    segmentStartIndex = -1; // Reset segmentStartIndex
            }
        }
    }

    // Check if there's an unclosed range at the end
    if (segmentStartIndex != -1) {
            SegmentEntry segment;
            segment.baseNumber = segmentStartIndex;
            //printf("Free segment: base=%d, size=%d\n", segment.baseNumber, segment.size); //was wondering if we should be printing the free spaces to make the simulation nicer
            segment.size = PHYSICAL_MEMORY_SIZE - segmentStartIndex;
            freeSegments[freeSegmentsIndex++] = segment;
    }

    return freeSegments;
}

int main (){
    return 0;
}
