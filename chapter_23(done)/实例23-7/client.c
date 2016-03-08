#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "iolib.h"

#define MAX_LINE 100
    
int main(int argc, char *argv[])
{
     struct sockaddr_in sin;
     char buf[MAX_LINE];
     int s_fd;
	int port = 8000;
	char *str = "test sting"; 
	int n;
    
     if (argc > 1)
          str = argv[1];
    
     bzero(&sin, sizeof(sin));

     sin.sin_family = AF_INET;
     inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); 
     sin.sin_port = htons(port); 
    
	if( (s_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("fail to creat socket");
		exit(1);
	}

	if(connect(s_fd, (struct sockaddr_in *) &sin, sizeof(sin)) == -1){
		perror("fail to connect");
		exit(1);
	}

	n = my_write(s_fd, str, strlen(str) + 1); 
	if(n == -1)
		exit(1);
	
	n = my_read(s_fd, buf, MAX_LINE);
	if(n == -1)
		exit(1);	
     
	printf("recive from server: %s\n", buf);

    if(close(s_fd) == -1){ 
     	perror("fail to close");
		exit(1);
	}

	return 0;
}
