#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1000

int main(int argc, char* argv[]){
    
    // exit unsuccessfully if no search term is specified
    if (argc < 2){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    
    // get the search term
    char *search_term = argv[1];
    
    if (argc == 2){
        char line[BUFFER_SIZE];
        while (fgets(line, BUFFER_SIZE, stdin)) {
            if (strstr(line, search_term)){
            printf("%s", line);
            }
        }
        return 0;
    }

    for (int i =2; i< argc; i++){
		FILE *file = fopen(argv[i], "r");
                
                // exit if the file cannot be found
		if(file == NULL){
			printf("wgrep: cannot open file\n");
			exit(1);
		}
	    char *line = NULL;
        size_t len_line = 0;
        ssize_t read;
        
        // check if the search term is contained in the line
        while ((read = getline(&line, &len_line, file))!=-1) {
            if (strstr(line, search_term)){
            printf("%s", line);
            
            }
        }
        free(line);
        fclose(file);
    }


    return 0;
}