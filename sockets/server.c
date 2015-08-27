#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
	printf("I'M SERVER, HE HE HE");
	int socket_desc, c, new_socket;
	char *message;
	struct sockaddr_in server, client;
	
	// Initializeeeeeeee
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1){
		printf("cannot create socket");
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(9997);
	
	// =========================
	// =        BLAB           =
	// =========================
	
	// Bind
	if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0){
		puts("Bind failed");
	}
	puts("Bind server done");
	
	// Listen
	listen(socket_desc, 10);
	
	// Accept
	puts("Waiting for clients ......");
	c = sizeof(struct sockaddr_in);
	while((new_socket = accept(socket_desc, 
								(struct sockaddr *)&client, 
								(socklen_t *)&c ))){
		if(new_socket < 0){
			perror("accept failed");
		}
		printf("Accepted new client at socket: %i\n", new_socket);
		
		// Begin
		message = "Hello client, :D\n\n";
		write(new_socket, message, strlen(message));
		puts("Sent message to client");
	}
	if(new_socket < 0){
		puts("Cannot create new sockets");
	}
	
	return 0;
}
