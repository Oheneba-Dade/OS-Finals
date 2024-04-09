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
/**
 * The function `trackNumberAllocatedFrames` counts the number of allocated frames in a given
 * `FrameTable`.
 * 
 * @param frameTable The `frameTable` parameter is a pointer to a `FrameTable` struct. The `FrameTable`
 * struct likely contains information about a set of frames, such as an array of frames or other
 * relevant data related to memory management. The function `trackNumberAllocatedFrames` iterates
 * through the
 * 
 * @return The function `trackNumberAllocatedFrames` returns the count of allocated frames in the
 * `frameTable`.
 */

int trackNumberAllocatedFrames(FrameTable* frameTable) {
	int allocatedCount = 0;
	for (int i=0; i< frameTable->capacity;i++){
		if (frameTable->frames[i].pageNumber != -1){
			allocatedCount+=1;
		}

	}
	return allocatedCount;
}

/**
 * The function checks if a frame in a frame table is allocated.
 * 
 * @param frameTable FrameTable is a data structure that keeps track of the status of each frame in the
 * memory. It typically contains information such as the page number currently stored in each frame.
 * @param frame The `frame` parameter represents the index of the frame in the frame table that we want
 * to check if it is allocated or not.
 * 
 * @return The function `frameIsAllocated` returns 1 if the frame is allocated (i.e., the page number
 * is not -1 in the frame table), and it returns 0 if the frame is not allocated.
 */
int frameIsAllocated(FrameTable* frameTable, int frame) {
	if (frameTable->frames[frame].pageNumber!=-1){
		return 0;
	}
	return 1;
}

/**
 * The function `firstFreeFrame` returns the index of the first free frame in a FrameTable structure.
 * 
 * @param frameTable The `frameTable` parameter is a pointer to a `FrameTable` struct. The `FrameTable`
 * struct likely contains information about the frames in a memory system, such as an array of frames.
 * The function `firstFreeFrame` iterates through the frames in the `frameTable` to
 * 
 * @return If a free frame is found in the frame table, the index of that frame is returned. If no free
 * frame is found, -1 is returned.
 */
int firstFreeFrame(FrameTable* frameTable) {
    for (int i=0; i<frameTable->capacity;i++){
        if (frameTable->frames[i].pageNumber ==-1) return i;
    }
    return -1;
}

void printFrameTable(FrameTable *frameTable) {
    printf("Frame Table:\n");
    printf("Capacity: %d\n", frameTable->capacity);
    printf("Frame Number\tPage Number\n");
    for (int i = 0; i < frameTable->capacity; i++) {
        printf("%d\t\t%d\t\t%d\n", frameTable->frames[i].frameNumber, frameTable->frames[i].pageNumber, frameTable->frames[i].processID);
    }
}

int memoryUtilizedByProcess(FrameTable *frameTable, int processID){
    int framesOccupied = 0;
    for (int i=0; i<frameTable->capacity;i++){
    if (frameTable->frames[i].processID== processID){
        framesOccupied+=1;
    }
    }
    return framesOccupied;
}
