#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int pid;
    int data_size;
    int stack_size;
    int text_size;
}Process;

/**
 * The function creates a process with specified text, data, and stack sizes based on a given filename.
 * 
 * @param filename The function `createProcessess` takes a filename as input and processes it to create
 * a `Process` struct. The filename is used to extract information such as file size, text size, data
 * size, stack size, and process ID. The function then assigns these values to the corresponding fields
 * in the
 * 
 * @return The function `createProcessess` is returning a `Process` structure that contains information
 * about the process, such as the data size, stack size, text size, and process ID.
 */
Process createProcess(char *filename){
    Process process;

    int size = getFileSize(filename);
    int textSize = size / 4;
    int dataSize = size / 4;
    int stackSize = size /2;
    process.data_size = dataSize;
    process.stack_size = stackSize;
    process.text_size = textSize;

    int len = strlen(filename);
    int id = 0;
    for (int i = 7; i < len - 2; i++) {
        id = id * 10 + (filename[i] - '0');
    }
    process.pid = id;
    return process;
}

// create processess based on the number specified and genrate segment table for them