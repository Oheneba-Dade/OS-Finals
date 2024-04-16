# OS-Finals

### This Project Seeks to Simulate Memory Segmentation in Operating Systems in the C Programming Language

### Link To The Video
https://www.youtube.com/watch?v=lYrlX1npLFg

### How to run the project

1. Clone the repository
2. Run the command ./simulation.sh

### Project Description
1. Simulation of processes using real C files.
2. Segments Implemented as Struct object
```C
typedef struct {
    int baseNumber;
    int size;
} SegmentEntry;
```
3. Process makes use of the Best-Fit algorithm, Compaction, for allocation and deallocation of memory
