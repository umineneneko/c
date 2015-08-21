#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

typedef struct {
	unsigned long ip_addr;
} in_addr;

int main(int argc, char *argv[]){
	printf("======Hello Sockets ======\r\n");
	char *message, server_reply[2000];
	int socket_desc, temp;
	struct sockaddr_in server;
	
	// CREATE a socket	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); // TCP: socket(2, 1, 0) UDP: socket(2, 2, 0)
	printf("1.%s : %d\n", "Result", socket_desc);
	message = socket_desc == -1 ? "Could not make a socket" : "A New socket is created";
	
	printf("--> %s\n", message);
	// DEFINE the target server
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	server.sin_addr.s_addr = inet_addr("192.168.2.18");
	// MAKE a connection
	temp = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
	printf("2.%s : %d\n", "Result", temp);
	message = temp < 0 ? "Could not make a Connection" : "Connection is established";	
	printf("--> %s\n", message);
	
	// SEND a message
	message = "GET / HTTP/1.1\r\n\r\n";
	temp = send(socket_desc, message, sizeof(message), 0);	
	printf("3.%s : %d\n", "Result", temp);
	message = temp < 0 ? "Could not send data" : "Message has been sent";	
	printf("--> %s\n", message);
	
	// RECEIVE the response
	temp = recv(socket_desc, server_reply, sizeof(server_reply), 0);	
	printf("4.%s : %d\n", "Result", temp);
	message = temp < 0 ? "Could not received the response" : server_reply;	
	printf("--> %s\n", message);
	
	//CLOSE socket
	close(socket_desc);
	return 1;
}
