#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "process.h"
#include "segments.h"
#include "physical_memory.h"
#include <math.h>
#include "utils.h"
#define MAX_PROCESSES 10
#define MAX_SEGMENTS 3
#define MAX_ATTEMPTS 5
#define FILE_DIRECTORY "processes/"


// Signal handler function for SIGILL
void sigillHandler(int signum) {
    printf("Segment size greater than physical memory available).\n");
    exit(1);
}


void displayStatistics(int deallocationAttempts, int memoryUsed, Process process) {
    printf("Statistics:\n");
    printf("Number of deallocation attempts: %d\n", deallocationAttempts);
}

int main(int argc, char *argv[]) {
    // Statistics variables for the simulation
    int deallocationAttempts = 0;
    int* physicalMemory = initializeMemory(1024);
    randomly_assign_segments(physicalMemory, 3, 6);
    printMemory(physicalMemory, 1024);

    printf("Calculating how many free segments exist currently...\n");
    findFreeSegments(physicalMemory);
    printf("\n");

    int numberOfProcess = atoi(argv[1]);
    
    //keep track of the segments assigned to each process
    SegmentTable assignedSegments[numberOfProcess];
    int currentSegmentTableToRemove = 0;

    if (numberOfProcess < 1 || numberOfProcess > MAX_PROCESSES)
    {
        printf("Invalid number of processes. Please try again.\n");
        return 1;
    }

   // Create an array of processes
    Process processes[MAX_PROCESSES];

    for(int i=0; i < numberOfProcess; i++) {
        char filename[50];
        sprintf(filename, "%sprocess%d.c", FILE_DIRECTORY, i + 1);
        Process process = createProcess(filename);
        int processSize = process.stack_size + process.data_size + process.text_size; // total process size
        printf("The size of process no: #%d = %d\n", i+1, processSize);
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

    printf("Attempting to find free space in memory for the %s of process #%d with size = %d\n", segmentName, i + 1, segmentSize);

    FreeSegmentsAndSize result = findFreeSegments(physicalMemory);
    SegmentEntry *freeSegments = result.freeSegmentsPointer;
    int numSegments = result.size;
    int baseNumber = bestFit(freeSegments, numSegments, segmentSize);
    printf("\n");
    
    // if (baseNumber == -1) { // If best fit returns -1, it means there is no available best fit currently
    //     printf("No best fit found for the %s of process #%d with size = %d\n", segmentName, i + 1, segmentSize);
    //     printf("Attempting to compact memory...\n");
    //     compactMemory(physicalMemory);
    //     printf("Memory compaction complete.\n");
    //     printf("Attempting to find free segment for the %s of process #%d with size = %d\n", segmentName, i + 1, segmentSize);
    //     baseNumber = bestFit(freeSegments, numSegments, segmentSize);
    // }

    // If after compaction, there is still no best fit, deallocate an earlier process and try again. while loop to try again to find a best fit.
    // This is just a placeholder


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
        printf("Memory deallocation complete.\n");
        printMemory(physicalMemory, 1024);
        currentSegmentTableToRemove = (currentSegmentTableToRemove + 1) % numberOfProcess;

        // Attempt to find a best fit again
        FreeSegmentsAndSize result = findFreeSegments(physicalMemory);
        SegmentEntry *freeSegments = result.freeSegmentsPointer;
        numSegments = result.size;

        baseNumber = bestFit(freeSegments, numSegments, segmentSize); 
        printf("\n");       
        // print the base number of the best fit
        if (baseNumber != -1) {
            printf("The base number of the best fit is %d\n", baseNumber);
        }
        else {
            printf("No best fit found after deallocation.\n");
            deallocationAttempts++;
        }
    }
    }

    table->segments[j].baseNumber = baseNumber;
    table->segments[j].size = segmentSize;
    assignedSegments[i] = *table;
    printf("Based on the best fit algorithm, the %s of process #%d will be stored in memory starting from base number %d\n", segmentName, i + 1, baseNumber);
    printSegmentTable(table);
    fillMemory(physicalMemory, baseNumber, segmentSize);

    double memoryUsed = round(((double)processSize / PHYSICAL_MEMORY_SIZE) * 100);
    printf("Percentage of Memory used by Process: %.2f KB\n", memoryUsed);
}

    printMemory(physicalMemory, 1024);
    }
}