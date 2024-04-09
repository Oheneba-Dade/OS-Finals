#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "segments.h"
#include "utils.h"
#define MAX_PROCESSES 10
#define FILE_DIRECTORY "processes/"

int generate_random_base_number() {
    return rand() % 1000;
}

int main() {
    int numProcesses;
    printf("Enter the number of processes (1-10): ");
    scanf("%d", &numProcesses);

    if (numProcesses < 1 || numProcesses > MAX_PROCESSES) {
        printf("Invalid number of processes. Please try again.\n");
        return 1;
    }

    Process processes[MAX_PROCESSES];
    SegmentTable segmentTables[MAX_PROCESSES];

    for (int i = 0; i < numProcesses; i++) {
        char filename[50];
        sprintf(filename, "%sprocess%d.c", FILE_DIRECTORY, i + 1); 
        Process process = createProcess(filename);
        processes[i] = process;
        SegmentTable *table =  createSegmentTable();
        table->pid = process.pid;
        
       for (int j = 0; j < 3; j++) {
        LogicalAddress address = generate_random_logical_address();
        int segmentNumber = address.segment_number;
        if (segmentNumber == 0) {
            table->segments[j].baseNumber = generate_random_base_number();
            table->segments[j].size = process.stack_size;
        } else if (segmentNumber == 1) {
            table->segments[j].baseNumber = generate_random_base_number();
            table->segments[j].size = process.text_size;
        } else if (j == 2) {
            table->segments[j].baseNumber = generate_random_base_number();
            table->segments[j].size = process.data_size;
        }
    }


    

        

    
}

return 0;
}

