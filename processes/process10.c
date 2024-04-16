#define  MAX_PROCESSES 10
#define  MEMORY_SIZE 1024

int generateRandomAddress(){
    // Define the range for the random number
    int lowerBound = 0;
    int upperBound = MEMORY_SIZE;

    // Generate a random number within the specified range
    int randomNumber = (rand() % (upperBound - lowerBound + 1)) + lowerBound;

    return randomNumber;
}

int generateRandomMemorySize(int lowerBound, int upperBound){
    if (upperBound > MEMORY_SIZE/2) {
        upperBound = MEMORY_SIZE/3;
    }
    int randomNumber = (rand() % (upperBound - lowerBound + 1)) + lowerBound; // Generate random number between 1 and less than half of MEMORY_SIZE
    return randomNumber;
}



void allocateMemory(int memory[], int address, int size){
    for (int i = address; i < address + size; i++) {
        memory[i] = 1; // Mark memory as allocated
    }
}
