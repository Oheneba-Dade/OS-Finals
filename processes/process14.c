# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

void createChildProcess();

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
	// The `for` loop is creating multiple child processes based on the value of `numberOfProcess
	for (int i = 0; i < numberOfProcess; i++){
	 createChildProcess();
	}
	
	 printf("Parent process number: %d\n", getpid());
	return 0;
}

/**
 * The function creates a child process and prints its process ID if successful.
 */
void createChildProcess(){
pid_t processId = fork();

if (processId < 0){
fprintf(stderr, "Failed to create child process \n");
exit(EXIT_FAILURE);
}

//The code snippet checks if the process ID is 0 and prints a message indicating it is
else if (processId == 0){
 printf("This is child process with process id %d \n", getpid());
 exit(EXIT_SUCCESS);
}
else{
wait(NULL);
}
}
