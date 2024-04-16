#include <stdio.h>
#include <stdlib.h>


void decompress(FILE *input_file) {
    char current_char;
    int count;
    
    // read the number 
    while (fread(&count, sizeof(int), 1, input_file) == 1) {
        fread(&current_char, sizeof(char), 1, input_file);

        // loop through the number of times and print the letter attached
        for (int i = 0; i < count; i++) {
            printf("%c", current_char);
        }
    }



}