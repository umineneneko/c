#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h> //resolve hostname to IP: hostent

int main(){
	printf("%s\n\n", "I'M A SERVER");
	char *list[] = {"it.dlu.edu.vn","www.google.com", NULL};
	char **host_name = list;
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	while(*host_name){
		
		if((he = gethostbyname(*host_name)) == NULL){
			herror("gethostname");
			return -1;
		}
		
		addr_list = (struct in_addr**)he->h_addr_list;
		
		for(i = 0; addr_list[i]!=NULL; i++){
			strcpy(ip, inet_ntoa(*addr_list[i]));
		}
		
		printf("\r%s resolved to %s\n", *host_name, ip);
		host_name++;
	}
	return 0;
}
