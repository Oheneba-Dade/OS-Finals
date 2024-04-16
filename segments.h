#ifndef OS_FINALS_SEGMENTS_H
#define OS_FINALS_SEGMENTS_H

#define MAX_SEGMENTS 3

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
void printSegmentTable(SegmentTable *table);

#endif //OS_FINALS_SEGMENTS_H
