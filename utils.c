#include <stdio.h>
#include <time.h>
#define MAX_SEGMENTS 4
#define MAX_OFFSET 100



typedef struct{
    int segment_number;
    int offset;
}LogicalAddress;


LogicalAddress generate_random_logical_address(){
    LogicalAddress address;

     // Generate a random number within the inclusive range
    address.segment_number = (rand() % (MAX_SEGMENTS+ 1));
    address.offset =  (rand() % (MAX_OFFSET + 1));
    return address;

}

int main (){
    srand(time(NULL));
    for (int i=0; i<4; i++){
        printf("Number is %d and offset is %d\n", generate_random_logical_address().segment_number, generate_random_logical_address().offset);
    }
    return 0;
}