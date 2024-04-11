#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MEMORY_SIZE 1024

void randomly_assign_segments(int memory[], int num_segments, int segment_size) {
    srand(time(NULL)); // Seed the random number generator with current time

    for (int i = 0; i < num_segments; i++) {
        int start_index = rand() % (MEMORY_SIZE - segment_size + 1); // Random start index for the segment

        for (int j = 0; j < segment_size; j++) {
            memory[start_index + j] = 1; // Assign 1 to the memory locations within the segment
        }
    }
}

// int main() {
//     int memory[MEMORY_SIZE] = {0}; // Initialize memory with all zeros

//     randomly_assign_segments(memory, 4, 15); // Assign 4 segments of size 15 randomly

//     // Print memory content for verification
//     printf("Memory content:\n");
//     for (int i = 0; i < MEMORY_SIZE; i++) {
//         printf("%d ", memory[i]);
//     }
//     printf("\n");

//     return 0;
// }
