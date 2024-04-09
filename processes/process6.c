#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include <signal.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

#include <pthread.h>


// the global variable
int global_variable;

// mutex for synchronization
pthread_mutex_t mutex;


// function to increment the variabe
void* increment_variable(int value){


		pthread_mutex_lock(&mutex);
		global_variable+=value;

		pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);

}

void *handleClient(void *client_socket){
   int client_sock = *((int *) client_socket);

  int read_size;
   char message[100];
   //Receive a message from client
	while( (read_size = recv(client_sock , message , sizeof(message) , 0)) > 0 )
	{
		int increment_val = atoi(message);
		void* server_message =  increment_variable(increment_val);

	
		//Send the message back to client
		write(client_sock , server_message , sizeof(server_message));
	}
   close(client_sock);
   pthread_exit(NULL);
}






int main()
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	int client_message[10];
	int server_message = 0;
	
	//Create socket
	socket_desc = socket(AF_INET6 , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET6;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

/// creating threads to handle the requests
	pthread_t clientThreads[5];

	for (int i=0; i<5; i++){
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}


	 pthread_t client;
	  if (pthread_create(&client, NULL, handleClient, &client_sock)!=0){
		perror("Could not create thread for client");
		close(client_sock);
	  }

	  for (int i=0; i<5; i++){
		pthread_join(clientThreads[i], NULL);
	  }
	}

	 
	
	return 0;
}