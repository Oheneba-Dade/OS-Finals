#include <stdio.h>
#include <stdlib.h>

void compress(char *files[], int num_files) {
int count = 1;  //set count to one to assume a character has been seen
char current;
char previous = '\0';
    
    // exit if the file cannot be opened
    for (int i = 0; i < num_files; i++) {
        FILE *file = fopen(files[i], "r");
        if (file == NULL) {
            exit(1);
        }
        
        // read the file while EOF has not reached
        while (fread(&current, sizeof(char), 1, file)) {
            if (current == previous) {
                count++;
            } else {
              if (previous != '\0'){
              fwrite(&count, sizeof(int), 1, stdout);
              fwrite(&previous, sizeof(char), 1, stdout);
                
              }
               count =1;
              
            }
              previous = current;
        }

        fclose(file);
    }
    
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&previous, sizeof(char), 1, stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    // pass in the array of filenames and the no of arguments
    compress(argv + 1, argc-1);

    return 0;
}
