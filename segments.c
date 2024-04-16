#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "segments.h"

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
        table->segments[i].baseNumber = 0;
        table->segments[i].size = 0;
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


// int main() {
//     SegmentTable* table = createSegmentTable();

//     // Test printing the created SegmentTable
//     printf("Capacity: %d\n", table->capacity);
//     printf("Segment Entries:\n");
//     for (int i = 0; i < table->capacity; i++) {
//         printf("Segment %d: Base Number = %d, Size = %d\n", i + 1, table->segments[i].baseNumber, table->segments[i].size); // Use size instead of size
//     }
//     signal(SIGSEGV, sigsegv_handler);
//     // Call translate_logical_address with some values
//     printf("The number is %d\n", translate_logical_address(table, 2, 3));
    

//     free(table);

//     return 0;
// }
