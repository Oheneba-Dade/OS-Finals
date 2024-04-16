#include <stdio.h>
#define NUM_FRAMES 10

// Define the structure for the frame
typedef struct {
    int frameNumber;
    int pageNumber;
    int processID;
} FrameEntry;

/**
 * The above type is a struct representing a frame table with a specified capacity and an array of
 * frame entries.
 * @property {int} capacity - The `capacity` property in the `FrameTable` struct represents the maximum
 * number of frames that can be stored in the frame table. It indicates the total number of frames that
 * the frame table can hold at any given time.
 * @property {FrameEntry} frames - The `frames` property in the `FrameTable` struct is an array of
 * `FrameEntry` elements. Each `FrameEntry` element represents a frame in the frame table.
 */
typedef struct {
    int capacity;
    FrameEntry frames[NUM_FRAMES];
} FrameTable;

/**
 * The function initializes a frame table by setting the frame numbers and page numbers for each frame.
 * 
 * @param frameTable The `frameTable` parameter is a pointer to a `FrameTable` struct. The `FrameTable`
 * struct likely contains information about the frame table used in a system, such as the capacity of
 * the frame table and an array of frames. The function `initializeFrameTable` initializes the frame
 * table
 */
void initializeFrameTable(FrameTable* frameTable) {
    frameTable->capacity = NUM_FRAMES;
    int capacity = frameTable->capacity;
    printf("capacity is %d\n", capacity);

    for (int i = 0; i < capacity; i++) {
        frameTable->frames[i].frameNumber = i;
        frameTable->frames[i].pageNumber = -1;
        frameTable->frames[i].processID = -1;
    }
}

/**
 * This function calculates the number of free frames in a given frame table.
 * 
 * @param frameTable FrameTable* frameTable is a pointer to a structure that represents a table of
 * frames in memory. Each frame in the table contains information about a page, such as the page number
 * currently stored in the frame.
 * 
 * @return The function `trackNumberFreeFrames` returns the number of free frames in the `FrameTable`
 * structure.
 */
int trackNumberFreeFrames(FrameTable* frameTable) {
    int freeCount = 0;
    for (int i = 0; i < frameTable->capacity; i++) {
        if (frameTable->frames[i].pageNumber == -1) {
            freeCount += 1;
        }
    }
    return freeCount;
}