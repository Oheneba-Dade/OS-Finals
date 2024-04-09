#ifndef OS_FINALS_PHYSICAL_MEMORY_H
#define OS_FINALS_PHYSICAL_MEMORY_H

typedef struct {
    int baseNumber;
    int size;
} SegmentEntry;

typedef struct {
    int capacity;
    int pid;
    SegmentEntry segments[3]; // Maximum of 3 entries for the segment table
} SegmentTable;

SegmentTable* createSegmentTable();
#endif //OS_FINALS_PHYSICAL_MEMORY_H
