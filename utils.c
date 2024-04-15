#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include "segments.h"
#include <sys/stat.h>
#include "process.h"
#include <string.h>
#include "utils.h"
#define MAX_OFFSET 100
#define PHYSICAL_MEMORY_SIZE 1024
#define MAX_NUM_FREE_SEGMENTS 512 
// This is because the highest number of free segments for the physical memory of size 1024 is when the free segments alternate, which would be equal to 512. 




LogicalAddress generate_random_logical_address(){
    LogicalAddress address;

     // Generate a random number within the inclusive range
    address.segment_number = (rand() % (MAX_SEGMENTS+ 1));
    address.offset =  (rand() % (MAX_OFFSET + 1));
    return address;

}



int bestFit(SegmentEntry freeSegments[], int segmentSize) {
    int numFreeSegments = sizeof(freeSegments) / sizeof(freeSegments[0]);
    printf("Number of free segments: %d\n", numFreeSegments);
    int bestFitBaseAndSize[2];
    int bestFitBase = -1;
    int bestFitSize = INT_MAX;
    // bestFitBaseAndSize[0] = -1; // Default value indicating no best fit found
    // bestFitBaseAndSize[1] = INT_MAX; // Set to maximum possible value initially
    for (int i = 0; i < numFreeSegments; i++) {
        if (segmentSize <= freeSegments[i].size) {
            int difference = freeSegments[i].size - segmentSize;
            if (difference < bestFitSize) {
                // bestFitBaseAndSize[0] = freeSegments[i].baseNumber;
                // bestFitBaseAndSize[1] = freeSegments[i].size;
                printf("Got here wai!\n");
                bestFitBase = freeSegments[i].baseNumber;
                bestFitSize = freeSegments[i].size;
            }
        }
    }
    return bestFitBase;
}


/**
 * @param physicalMemory An array that represents the physical memory
 * @return The function `findFreeSegments` returns a pointer to an array of `SegmentEntry` structures
 * representing the free segments in the `physicalMemory` array.
 */
SegmentEntry* findFreeSegments(int physicalMemory[]) {
    physicalMemory[0] = 1;
    physicalMemory[1] = 1;
    physicalMemory[2] = 1;  
    physicalMemory[3] = 1;

    physicalMemory[10]=1;
    physicalMemory[11]=1;
    physicalMemory[12]=1;
    physicalMemory[13]=1;

    physicalMemory[20]=1;
    physicalMemory[21]=1;
    physicalMemory[22]=1;
    physicalMemory[23]=1;
    
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

/**
 * The getFileSize function retrieves the size of a file specified by the filename parameter.
 * 
 * @param filename The `filename` parameter is a pointer to a character array that represents the name
 * of the file to be retrieved
 * 
 * @return The function `getFileSize` returns the size of the file specified by the `filename`
 * parameter.
 */
int getFileSize(char *filename){
    struct stat st;
    stat(filename, &st);
    int size = st.st_size;
    return size;
}




