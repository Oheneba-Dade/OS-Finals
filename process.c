#include <stdio.h>
typedef struct{
    int data[100];
    int stack[100];
    int* heap;
}ProcessComponent

typedef struct{
    int id;
    ProcessComponent component;
}Process
