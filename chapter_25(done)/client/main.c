#include "common.h"

int main(void)
{
	char cline[COMMAND_LINE]; 
	struct command_line command; 
	int sock_fd;
	struct sockaddr_in sin;

	printf("myftp$: "); 
	fflush(stdout); 

	while(fgets(cline, MAX_LINE, stdin) != NULL){ 
		if(split(&command, cline) == -1)
			exit(1);
		if(strcasecmp(command.name, "get") == 0){ 
			if(do_get(command.argv[1], command.argv[2], sock_fd) == -1)
				exit(1); 
		}else if(strcasecmp(command.name, "put") == 0){ 
			if(do_put(command.argv[1], command.argv[2], sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "cd") == 0){ 
			if(do_cd(command.argv[1]) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "!cd") == 0){ 
			if(do_serv_cd(command.argv[1], sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "ls") == 0){ 
			if(do_ls(command.argv[1]) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "!ls") == 0){ 
			if(do_serv_ls(command.argv[1], sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "connect") == 0){ 
			if(do_connect(command.argv[1], &sin, &sock_fd) == -1)
				exit(1);
		}else if(strcasecmp(command.name, "bye") == 0){ 
			if(do_bye(sock_fd) == -1)
				exit(1);
			break;
		}else{ 
			printf("wrong command\n");
			printf("usage : command arg1, arg2, ... argn\n");
		}
		
		printf("myftp$: ");
		fflush(stdout);
	}
     
	if(close(sock_fd) == -1){ 
		perror("fail to close");
		exit(1);
	}

	return 0;
}
