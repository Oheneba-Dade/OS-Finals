#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000 //define the buffer size

int main (int argc, char *argv[]){
	// exit successfully if no files are specified
	if (argc <2){
		exit(0);
	}

	for (int i =1; i< argc; i++){
		FILE *file = fopen(argv[i], "r");

		if(file == NULL){
			// exit with return of 1 if there is a problem with the file
			printf("wcat: cannot open file\n");
			exit(1);
		}
		// specify buffer size
	    char line[BUFFER_SIZE];
        //read file by line and print it
        while (fgets(line, BUFFER_SIZE, file)) {
            printf("%s", line);
        }
        fclose(file);
    }
	return 0;	
}