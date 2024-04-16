#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "segments.h"
#include "physical_memory.h"
#include "utils.h"
#define MAX_PROCESSES 10
#define MAX_SEGMENTS 3
#define MAX_ATTEMPTS 5
#define FILE_DIRECTORY "processes/"


// if best fit returns -1, it means there is no space so we first check if compaction will work, if it does not work, then we deallocate earlier processes

// Signal handler function for SIGILL
void sigillHandler(int signum) {
    printf("Segment size greater than physical memory available).\n");
    exit(1);
}

int main() {
    // Statistics variables for the simulation
    int deallocationAttempts = 0;

    int* physicalMemory = initializeMemory(1024);
    randomly_assign_segments(physicalMemory, 3, 6);
    printMemory(physicalMemory, 1024);
    printf("Calculating how many free segments exist currently...\n");
    findFreeSegments(physicalMemory);
    int numProcesses;
    printf("Enter the number of processes (1-10): \n");
    scanf("%d", &numProcesses);

    //keep track of the segments assigned to each process
    SegmentTable assignedSegments[numProcesses ];
    int currentSegmentTableToRemove = 0;

    if (numProcesses < 1 || numProcesses > MAX_PROCESSES)
    {
        printf("Invalid number of processes. Please try again.\n");
        return 1;
    }

    // flag array to keep track of assigned segments
    // int assignedSegments[MAX_SEGMENTS] = {0};
    Process processes[MAX_PROCESSES];

    for(int i=0; i < numProcesses; i++) {
        char filename[50];
        sprintf(filename, "%sprocess%d.c", FILE_DIRECTORY, i + 1);
        Process process = createProcess(filename);
        printf("The size of process no: #%d = %d\n", i+1, process.stack_size + process.data_size + process.text_size);
        processes[i] = process;
        SegmentTable *table = createSegmentTable();
        table->pid = process.pid;

        for (int j = 0; j < 3; j++) {
        int segmentSize;
        const char *segmentName;

        switch (j) {
            case 0:
                segmentSize = process.stack_size;
                segmentName = "stack";
                break;
            case 1:
                segmentSize = process.text_size;
                segmentName = "text";
                break;
            case 2:
                segmentSize = process.data_size;
                segmentName = "data";
                break;
            default:
                break;
        }

    printf("Attempting to find free segment for the %s of process #%d with size = %d\n", segmentName, i + 1, segmentSize);

    FreeSegmentsAndSize result = findFreeSegments(physicalMemory);
    SegmentEntry *freeSegments = result.freeSegmentsPointer;
    int numSegments = result.size;

    int baseNumber = bestFit(freeSegments, numSegments, segmentSize);
    
    // if (baseNumber == -1) { // If best fit returns -1, it means there is no available best fit currently
    //     printf("No best fit found for the %s of process #%d with size = %d\n", segmentName, i + 1, segmentSize);
    //     printf("Attempting to compact memory...\n");
    //     compactMemory(physicalMemory);
    //     printf("Memory compaction complete.\n");
    //     printf("Attempting to find free segment for the %s of process #%d with size = %d\n", segmentName, i + 1, segmentSize);
    //     baseNumber = bestFit(freeSegments, numSegments, segmentSize);
    // }


    if (baseNumber == -1) {
        printf("No space after compaction...\n");

        while (baseNumber == -1 ) {
        printf("Attempting to free space by deallocating an earlier process...\n");
        printf("Deallocating process with PID = %d\n", assignedSegments[currentSegmentTableToRemove].pid);
        // calculate the total size of the process to be deallocated using the assignedSegments array
        int totalSize = 0;
        SegmentEntry *segments = assignedSegments[currentSegmentTableToRemove].segments;
        
        for (int k = 0; k < 3; k++) {
            printf("Segment size = %d\n", segments[k].size);
            totalSize += segments[k].size;
        }

        printf("The total size of this process being removed is %d\n", totalSize);
        deallocateMemory(physicalMemory, segments[0].baseNumber, totalSize);
        currentSegmentTableToRemove = (currentSegmentTableToRemove + 1) % numProcesses;
    }
    }
    table->segments[j].baseNumber = baseNumber;
    table->segments[j].size = segmentSize;
    assignedSegments[i] = *table;
    // printf("This is the segment size i am looking for %d\n",assignedSegments[i].segments[j].size);
    fillMemory(physicalMemory, baseNumber, segmentSize);

}

        printMemory(physicalMemory, 1024);
    }
}