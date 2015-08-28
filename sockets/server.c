#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

void *connection_handler(void*);

int main(){
	printf("I'M SERVER, HE HE HE\r\n");
	int socket_desc, c, new_socket, *new_sock;
	
	struct sockaddr_in server, client;
	
	// Initializeeeeeeee
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1){
		printf("cannot create socket");
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(9995);
	
	// =========================
	// =        BLAB           =
	// =========================
	
	// Bind
	int reuse = 1;
	if( setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, (char*) &reuse,
		sizeof(int))==1 ){
		puts("Cannot reuse port");
	}else{
		puts("re-use port 9995");
	}
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
		printf("At: %s\n", inet_ntoa(client.sin_addr));
		
		// Assign to a new thread
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = new_socket;
		if(pthread_create(&sniffer_thread, NULL, 
			connection_handler, (void *)new_sock) < 0){
			perror("Could not create a new thread");
		}
		
	}
	if(new_socket < 0){
		puts("Cannot create new sockets");
	}
	close(socket_desc);
	return 0;
}

void* connection_handler(void* socket_desc){
	int read_size, sock = *(int*)socket_desc;
	char client_message[2000];
		// Begin
		char *message = "Hello client, say something to me! :D\n\n";
		write(sock, message, strlen(message));
		puts("Sent message to client");
		
	while( (read_size = recv(sock, client_message, 2000, 0)) >0){
		write(sock, client_message, strlen(client_message));
	}
	if(read_size == 0){
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1){
		perror("Recv failed");
	}
	free(socket_desc);
	return 0;
}

