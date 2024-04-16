#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "segments.h"

/**
 * The SegmentEntry struct contains two integer fields, baseNumber and size.
 * @property {int} baseNumber - The `baseNumber` property in the `SegmentEntry` struct represents the
 * starting number or value of a segment in the physical memory.
 * @property {int} size - The `size` property in the `SegmentEntry` struct represents the size of the
 * segment entry. It indicates the number of elements or items in the segment.
 */


/**
 * The SegmentTable struct represents a segment table with a capacity, process ID, and an array of
 * SegmentEntry structures with a maximum of 3 entries.
 * @property {int} capacity - The `capacity` property in the `SegmentTable` struct represents the
 * maximum number of entries that can be stored in the `segments` array. In this case, the `segments`
 * array has a maximum capacity of 3 entries.
 * @property {int} pid - The `pid` property in the `SegmentTable` struct represents the Process ID
 * associated with the segment table. It is used to identify the process to which the segment table
 * belongs.
 * @property {SegmentEntry} segments - The `segments` property in the `SegmentTable` struct is an array
 * of `SegmentEntry` structs. It has a maximum capacity of 3 entries
 */

/**
 * The function creates a SegmentTable structure with a capacity of 3 and initializes each SegmentEntry
 * with default values.
 * 
 * @return A pointer to a dynamically allocated SegmentTable structure is being returned.
 */
SegmentTable* createSegmentTable() {
    // Allocate memory for the SegmentTable structure
    SegmentTable* table = (SegmentTable*)malloc(sizeof(SegmentTable));
    if (table == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    table->capacity = 3;

    // Initialize each SegmentEntry with default values
    for (int i = 0; i < table->capacity; i++) {
        table->segments[i].baseNumber = -1;
        table->segments[i].size = -1;
    }

    return table;
}

// Signal handler
void sigsegv_handler(int sig) {
    printf("Invalid segment number\n");
    exit(1);
}

int translate_logical_address(SegmentTable *segment_table, int segment_number, int offset) {
    // Check if segment number is valid
    if (segment_number < 0 || segment_number >= segment_table->capacity) {
        raise(SIGSEGV);
    }

    if (offset < 0 || offset > segment_table->segments[segment_number].size) {
        raise(SIGSEGV);
    }
   
    int base_number = segment_table->segments[segment_number].baseNumber;
    return base_number + offset;
}

void printSegmentTable(SegmentTable *table) {
    printf("----------------------------------\n");
    printf("| Segment | Base Number | Size    |\n");
    printf("----------------------------------\n");
    for (int i = 0; i < MAX_SEGMENTS; i++) {
        const char *segmentName;
        switch (i) {
            case 0:
                segmentName = "Stack";
                break;
            case 1:
                segmentName = "Text";
                break;
            case 2:
                segmentName = "Data";
                break;
            default:
                break;
        }
        printf("| %-7s | %-11d | %-7d |\n", segmentName, table->segments[i].baseNumber, table->segments[i].size);
    }
    printf("----------------------------------\n");
}

void printSegmentsOccupyingMemory(SegmentTable assignedSegments[], int numberOfProcesses) {
    printf("Printing The Memory Allocation For Each Process:\n");
    sleep(2);
    for (int i = 0; i < numberOfProcesses; i++) {
        if (assignedSegments[i].pid != 1) {
            printf("Memory allocated for process with ID #%d\n", assignedSegments[i].pid);
            printSegmentTable(&assignedSegments[i]);
        }
    }
}