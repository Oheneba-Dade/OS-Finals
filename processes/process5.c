/*
	C ECHO client example using sockets
*/
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <stdlib.h>

int main() {
	int sock;
	struct sockaddr_in server;
	
	int server_reply;
	
	//Create socket
	sock = socket(AF_INET6 , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("0:0:0:0:0:0:0:1");
	server.sin_family = AF_INET6;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
	
	//keep communicating with server
	while(1)
	{
		int increment_val = 10;

		
		
		//Send some data
		if( send(sock , increment_val , sizeof(increment_val) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , &server_reply , sizeof(server_reply) , 0) < 0)
		{
			puts("recv failed");
			break;
		}

		printf("Server reply : %d", server_reply);

		exit(0);
		
		
	}

	
	close(sock);
	return 0;
}
