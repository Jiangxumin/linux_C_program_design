#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFES PIPE_BUF

void err_quit(char * msg){
	perror( msg );
	exit(1);
}

int main ( void ) 
{
	int fd[2];
	char buf[BUFSZ]; 
	pid_t pid;
	int len;
	
	if ( (pipe(fd)) < 0 ) 
		err_quit( "pipe" );
	
	if ( (pid = fork()) < 0 )  
		err_quit("fork");
	else if ( pid == 0 ){	
		close ( fd[0] );  
		write(fd[1], "hello brother!", 14 );  
		exit(0);
	}
	
	if ( (pid = fork()) < 0 )  
		err_quit("fork");
	else if ( pid > 0 ){   
		close ( fd[0] );
		close ( fd[1] );
		exit ( 0 );
	}
	else {		
		close ( fd[1] );  
		len = read (fd[0], buf, BUFS ); 
		write(STDOUT_FILENO, buf, len);
		exit(0);
	}
}
