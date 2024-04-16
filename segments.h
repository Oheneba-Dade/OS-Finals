#ifndef OS_FINALS_SEGMENTS_H
#define OS_FINALS_SEGMENTS_H

#define MAX_SEGMENTS 3

/**
 * The SegmentEntry struct contains two integer fields, baseNumber and size.
 * @property {int} baseNumber - The `baseNumber` property in the `SegmentEntry` struct represents the
 * starting number or value of a segment in the physical memory.
 * @property {int} size - The `size` property in the `SegmentEntry` struct represents the size of the
 * segment entry. It indicates the number of elements or items in the segment.
 */
typedef struct {
    int baseNumber;
    int size;
} SegmentEntry;

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
typedef struct {
    int capacity;
    int pid;
    SegmentEntry segments[3]; // Maximum of 3 entries for the segment table
} SegmentTable;

SegmentTable* createSegmentTable();
void printSegmentTable(SegmentTable *table);

#endif //OS_FINALS_SEGMENTS_H
