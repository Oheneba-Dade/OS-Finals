# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

void chainChildProcess(int processNumber);
int main(int argc, char *argv[]){
        if (argc!=2){
	printf("Usage: %s <child process>\n", argv[0]);
	exit(EXIT_FAILURE);
	}
	int numberOfProcess = atoi(argv[1]);
	if (numberOfProcess <=0){
		fprintf(stderr, "Pass a positive number\n");
		exit(EXIT_FAILURE);
	}	
         chainChildProcess(numberOfProcess);
	return 0;
}

/**
 * The function chainChildProcess creates a chain of child processes, where each child process creates
 * another child process until a specified process number is reached, and then each child process
 * prints its process ID.
 * 
 * @param processNumber The parameter `processNumber` represents the number of child processes to be
 * created in the chain. Each child process will create another child process until `processNumber`
 * reaches 0.
 */

void chainChildProcess(int processNumber){
	if(processNumber<=0){
		printf("Hello from last child with process_id:%d\n", getpid());
		exit(EXIT_SUCCESS);
	}
	pid_t processId = fork();
	if (processId < 0){
	fprintf(stderr, "Failed to create child process \n");
	exit(EXIT_FAILURE);
}
	else if (processId == 0){
	 chainChildProcess(processNumber-1);
	}
	
	else{
		wait(NULL);
		printf("This is a process with id: %d\n", getpid());
		exit(EXIT_SUCCESS);
	}
	}
