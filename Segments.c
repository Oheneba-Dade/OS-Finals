// Define The Structure For The Segments

typedef struct {
  int baseNumber;
  int offset;
} SegmentEntry;

typedef struct {
    int capacity;
    SegmentEntry segments[100]; //will change with constant value later
} SegmentTable;
