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
#define MAX_NUM_FREE_SEGMENTS 512  // This is because the highest number of free segments for the physical memory of size 1024 is when the free segments alternate, which would be equal to 512. 
#define MEMORY_SIZE 1024



LogicalAddress generate_random_logical_address(){
    LogicalAddress address;

     // Generate a random number within the inclusive range
    address.segment_number = (rand() % (MAX_SEGMENTS+ 1));
    address.offset =  (rand() % (MAX_OFFSET + 1));
    return address;

}



/**
 * The function `bestFit` finds the best fit base number for a segment of a given size among a list of
 * free segments.
 * 
 * @param freeSegments The `freeSegments` parameter is an array of `SegmentEntry` structures. 
 * @param numFreeSegments The `numFreeSegments` parameter represents the number of free segments in the
 * `freeSegments` array. This value is used to determine the size of the array and iterate over its
 * elements in the function.
 * @param segmentSize The `segmentSize` parameter in the `bestFit` function represents the size of the
 * segment that needs to be allocated. This function is designed to find the best fit for this segment
 * size within the array of free segments provided.
 * 
 * @return The function `bestFit` is returning the base number of the best fit segment for a given
 * segment size among the free segments provided.
 */
int bestFit(SegmentEntry freeSegments[], int numFreeSegments, int segmentSize) {
    // int numFreeSegments = sizeof(freeSegments) / sizeof(freeSegments[0]);
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
                bestFitBase = freeSegments[i].baseNumber;
                bestFitSize = freeSegments[i].size;
            }
        }
    }
    
    return bestFitBase;
}



/**
 * The function `findFreeSegments` iterates through a physical memory array to find free segments and
 * their sizes, storing them in a dynamically allocated array of `SegmentEntry` structs.
 * 
 * @param physicalMemory The `physicalMemory` array represents the physical memory in the system. Each
 * element in the array corresponds to a memory block, and a value of 0 indicates that the memory block
 * is free.
 * 
 * @return The function `findFreeSegments` is returning a struct of type `FreeSegmentsAndSize`. This
 * struct contains a pointer to an array of `SegmentEntry` called `freeSegments` and an integer `size`
 * indicating the number of free segments found in the `physicalMemory` array.
 */
FreeSegmentsAndSize findFreeSegments(int physicalMemory[]) {
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
                    printf("Free segment: base=%d, size=%d\n", segment.baseNumber, segment.size); //was wondering if we should be printing the free spaces to make the simulation nicer
                    freeSegments[freeSegmentsIndex++] = segment;
                    segmentStartIndex = -1; // Reset segmentStartIndex
            }
        }
    }

    // Check if there's an unclosed range at the end
    if (segmentStartIndex != -1) {
            SegmentEntry segment;
            segment.baseNumber = segmentStartIndex;
            printf("Free segment: base=%d, size=%d\n", segment.baseNumber, PHYSICAL_MEMORY_SIZE - segmentStartIndex); //was wondering if we should be printing the free spaces to make the simulation nicer
            freeSegments[freeSegmentsIndex++] = segment;
    }

    FreeSegmentsAndSize result;
    result.freeSegmentsPointer = freeSegments;
    result.size = freeSegmentsIndex;
    return result;
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


/**
 * The function randomly assigns segments of a specified size within a memory array by setting the
 * values to 1.
 * 
 * @param memory The `memory` parameter is an array representing the memory where segments will be
 * randomly assigned. The function will assign segments of size `segment_size` by setting the values in
 * the memory array to 1 within those segments. The number of segments to assign is specified by
 * `num_segments`.
 * @param num_segments The `num_segments` parameter in the `randomly_assign_segments` function
 * specifies the number of memory segments that need to be randomly assigned in the `memory` array.
 * Each segment will have a size specified by the `segment_size` parameter.
 * @param segment_size The `segment_size` parameter in the `randomly_assign_segments` function
 * represents the size of each memory segment that will be randomly assigned in the `memory` array.
 * This size determines how many memory locations within the array will be set to 1 for each segment.
 */
void randomly_assign_segments(int memory[], int num_segments, int segment_size) {
    srand(time(NULL)); // Seed the random number generator with current time

    for (int i = 0; i < num_segments; i++) {
        int start_index = rand() % (MEMORY_SIZE - segment_size + 1); // Random start index for the segment

        for (int j = 0; j < segment_size; j++) {
            memory[start_index + j] = 1; // Assign 1 to the memory locations within the segment
        }
    }
}