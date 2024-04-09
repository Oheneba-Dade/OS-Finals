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
int main (int argc, char* argv[]){
    if (argc < 2){

        //exit unsuccessfully if no file is specified
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i =1; i< argc; i++){
        FILE *file = fopen(argv[i], "r");
        if(file == NULL){
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
		}

        decompress(file);

    }
    return 0;

}