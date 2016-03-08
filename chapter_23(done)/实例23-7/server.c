#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "iolib.h"

#define MAX_LINE 100

void my_fun(char * p)
{
	if(p == NULL) /* ¿Õ´® */
		return;

	for (; *p != '\0'; p++)
		if(*p >= 'A'&& *p <= 'Z')
			*p = *p -'A'+ 'a';
}

int main(void)
{
     struct sockaddr_in sin;
     struct sockaddr_in cin;
     int l_fd;
     int c_fd;
     socklen_t len;
     char buf[MAX_LINE];
     char addr_p[INET_ADDRSTRLEN]; 
     int port = 8000;
	int n; 
       
     bzero(&sin, sizeof(sin));

     sin.sin_family = AF_INET; 
     sin.sin_addr.s_addr = INADDR_ANY; 
     sin.sin_port = htons(port); 
    
	if( (l_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ 
		perror("fail to creat socket");
		exit(1);
	}

	if(bind(l_fd, (struct sockaddr *) &sin, sizeof(sin)) == -1){
		perror("fail to bind");
		exit(1);
	}

	if(listen(l_fd, 10) == -1){
		perror("fail to listen");
		exit(1);
	}
     
	printf("waiting ...\n");
    
	while(1){
		if( (c_fd = accept(l_fd, (struct sockaddr *) &cin, &len)) == -1){
			perror("fail to accept");
			exit(1);
		}

		n = my_read(c_fd, buf, MAX_LINE); 
		if(n == -1)
			exit(1);
		else if(n == 0){ 
			printf("the connect has been closed\n");
			close(c_fd); 
			continue;
		}
    	
		inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));
		printf("client IP is %s, port is %d\n", addr_p, ntohs(cin.sin_port));
    		printf("content is : %s\n", buf); 
         
		my_fun(buf); 

		n = my_write(c_fd, buf, n); 
		if(n == -1){ 
			exit(1);
		}
		
		if(close(c_fd) == -1){ 
			perror("fail to close");
			exit(1);
		}
	}

	if(close(l_fd) == -1){ 
		perror("fail to close");
		exit(1);
	}


	return 0; 
}
