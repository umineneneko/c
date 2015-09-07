/*
 * A sample server supports multi-client connections
 */
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <sys/types.h>
 #include <netinet/in.h>
 #include <netdb.h>
 
 #define port "7000" 
 #define queue 10 // queue number
 
 void* get_in_addr(struct sockaddr *sa);
 
 int main()
 {
	 puts("Hello\n");
	 
	 // ==================================== VARIABLES
	 fd_set board; // list of file descriptor
	 fd_set temp_fds;
	 int fd_max;	 
	 
	 int listener; // server socket file descriptor
	 int new_fd; // new accept()ed socket descriptor
	 struct sockaddr_storage remote_addr; // client address, support both ipv4 + ipv6
	 socklen_t addr_len;
	 
	 char buf[256]; // client data
	 int n_bytes;
	 
	 char remote_ip[INET6_ADDRSTRLEN];
	 
	 int rebind = 1; // use in setsockopt()
	 int i, j, rv;
	 
	 struct addrinfo hints, *ai, *p;
	 
	 // ==================================== BEGIN
	 
	 FD_ZERO(&board);
	 FD_ZERO(&temp_fds);
	 
	 memset(&hints, 0, sizeof(hints));
	 hints.ai_family = AF_UNSPEC;
	 hints.ai_socktype = SOCK_STREAM;
	 hints.ai_flags = AI_PASSIVE;
	 
	 if((rv = getaddrinfo(NULL, port, &hints, &ai))!= 0){
		 fprintf(stderr, "select server: %s \n", gai_strerror(rv));
		 exit(1);
	 }
	 
	 for(p = ai; p != NULL; p = p->ai_next ){
		 listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		 if(listener < 0){
			 continue;
		 }
		 // lose the pesky "address already in use"
		 setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &rebind, sizeof(int));
		 
		 if(bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			 close(listener);
			 continue;
		 }
		 break;
	 }
	 
	 if(p == NULL){
		 fprintf(stderr, "select server: failed to bind\r\n");
		 exit(2);
	 }
	 
	 puts("Sever binded on port 7000");
	 freeaddrinfo(ai);
	 
	 // ============================================ LISTEN
	 if(listen(listener, queue) == -1){
		 perror("listen");
		 exit(3);
	 }
	 
	 puts("Listening ......\n");
	 FD_SET(listener, &board);
	 fd_max = listener;
	 
	 for(;;){
		temp_fds = board;
		if(select(fd_max+1, &temp_fds, NULL, NULL, NULL) == -1){
			perror("select");
			exit(4);
		}
	 
		for(i = 0; i<= fd_max; i++){
			if(FD_ISSET(i, &temp_fds)){
				if(i == listener){
						 puts("Someone has joined\n");
					addr_len = sizeof(remote_addr);
					new_fd = accept(listener, (struct sockaddr*)&remote_addr, &addr_len);
					
					if(new_fd == -1){
						perror("accept");
					} else {
						FD_SET(new_fd, &board);
						if(new_fd > fd_max){
							fd_max = new_fd;
						}
						printf("new connection from %s on socket %d\n",
							inet_ntop(remote_addr.ss_family,
								get_in_addr((struct sockaddr*)&remote_addr),
								remote_ip, INET6_ADDRSTRLEN),
							new_fd);
						
					}
				} else {
					
						
					if((n_bytes = recv(i, buf, sizeof(buf), 0)) <= 0){
					if(n_bytes == 0){
						printf("socket %d hung up", i);
					} else {
						perror("recv");
					}
					close(i);
					FD_CLR(i, &board);
				} else {
					puts("someone told something .");
					for(j = 0; j <= fd_max; j++){
						if(FD_ISSET(j, &board)){
							if(j != listener && j != i){
								if(send(j, buf, n_bytes, 0) == -1){
									perror("send");
								}
							}
						}
					}
				}
				}
			}
		}
	 }
	 
	 return 1;
 }
  
 void* get_in_addr(struct sockaddr *sa)
 {
	 if(sa->sa_family == AF_INET){
		 return &(((struct sockaddr_in*)sa)->sin_addr);
	 }
	 return &(((struct sockaddr_in6*)sa)->sin6_addr);
 }
	
 
 
