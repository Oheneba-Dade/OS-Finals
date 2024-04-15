#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "segments.h"
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
int main()
{
    int numProcesses;
    printf("Enter the number of processes (1-10): \n");
    scanf("%d", &numProcesses);

    if (numProcesses < 1 || numProcesses > MAX_PROCESSES)
    {
        printf("Invalid number of processes. Please try again.\n");
        return 1;
    }

    // flag array to keep track of assigned segments
    int assignedSegments[MAX_SEGMENTS] = {0};
    Process processes[MAX_PROCESSES];
    SegmentTable segmentTables[MAX_PROCESSES];

    for (int i = 0; i < numProcesses; i++)
    {
        char filename[50];
        sprintf(filename, "%sprocess%d.c", FILE_DIRECTORY, i + 1);
        Process process = createProcess(filename);
        processes[i] = process;
        SegmentTable *table = createSegmentTable();
        table->pid = process.pid;

        // generate random logical addresses
        for (int j = 0; j < MAX_SEGMENTS; j++)
        {
            int attempts = 0;

            // Generate logical address and attempt to assign segment
            while (attempts < MAX_ATTEMPTS)
            {
                LogicalAddress address = generate_random_logical_address();
                int segmentNumber = address.segment_number;

                // Check if segment number is already assigned
                if (assignedSegments[segmentNumber] == 0)
                {
                    // Mark segment as assigned
                    assignedSegments[segmentNumber] = 1;

                    // Assign base number and size based on segment type
                    if (segmentNumber == 0)
                    {
                        // find free segments in the physical memory
                        SegmentEntry *freeSegments = findFreeSegments(table->segments);
                        int baseNumber = bestFit(freeSegments, process.stack_size);
                        printf("Base number is %d\n", baseNumber);
                        table->segments[segmentNumber].baseNumber = baseNumber; 
                        table->segments[segmentNumber].size = process.stack_size;
                    }
                    else if (segmentNumber == 1)
                    {
                        SegmentEntry *freeSegments = findFreeSegments(table->segments);
                        int baseNumber = bestFit(freeSegments, process.stack_size);
                        printf("Base number is %d\n", baseNumber);
                        table->segments[segmentNumber].baseNumber = baseNumber; 
                        table->segments[segmentNumber].size = process.text_size;
                    }
                    else if (segmentNumber == 2)
                    {
                        SegmentEntry *freeSegments = findFreeSegments(table->segments);
                        int baseNumber = bestFit(freeSegments, process.stack_size);
                        printf("Base number is %d\n", baseNumber);
                        table->segments[segmentNumber].baseNumber = baseNumber;
                        table->segments[segmentNumber].size = process.data_size;
                    }

                    break;
                }
                else
                {
                    // Segment already assigned, try again
                    printf("Segment %d already assigned. Trying again...\n", segmentNumber);
                    attempts++;
                }
            }

            // Check if maximum attempts reached without assigning the segment
            if (attempts == MAX_ATTEMPTS)
            {
                break;
            }
        }
        printf("Segment table 1 size %d:\n",table->segments[0].baseNumber);
        printf("Segment table 1 size %d:\n",table->segments[1].baseNumber);
    }

    return 0;
}
