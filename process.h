#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int pid;
    int data_size;
    int stack_size;
    int text_size;
}Process;

Process createProcess(char *filename);