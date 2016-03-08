#include "common.h"

int main(void)
{
	struct sockaddr_in sin, cin;
	socklen_t len = sizeof(cin);
	int lfd, cfd, fd;
	pid_t pid;
	int sock_opt = 1; 
	int port;
	char path[MAX_LINE]; 
	struct stat statbuf; 

    	signal(SIGCHLD, SIG_IGN); 
	signal(SIGPIPE, SIG_IGN); 
     
	printf("initializing ...\n");
	
	if(configuration(&port, path) == -1){
		DEBUG_PRINT("error during initializing\n");
		exit(1);
	}

	while (1){ 
		DEBUG_PRINT ("waiting connection бн\n");
		
		cfd = accept(lfd, (struct sockaddr *)&cin, &len); 
		if(cfd == -1){
			perror("fail to accept");
			exit(1);
		}

		pid = fork(); 
		if(pid < 0){ 
			perror("fail to fork");
			exit(1);
		}else if(pid == 0){ 
			close(lfd);
			
			if(get_path(cfd, path) == -1){
				DEBUG_PRINT ("error during geting filepath\n");
				exit(1);
			}
	
			if(fstat(fd, &statbuf) < 0){
				perror("fail to get file status");
				exit(1);
			}

			if(!S_ISREG(statbuf.st_mode)){
				if(error_page(cfd) == -1){ 
					DEBUG_PRINT ("error during writing error-page\n");
					
					close(cfd);
					
					exit(1); 
				}
				
				close(cfd); 
				
				exit(0); 
			}

			if(statbuf.st_mode & S_IXOTH){ 
				dup2(cfd, STDOUT_FILENO);
				
				if(execl(path, path, NULL) == -1){
					perror("fail to exec");
	    				exit(1);
				}
			}

			if((fd = open(path, O_RDONLY)) < 0){ 
				if(error_page(cfd) == -1){ 
					DEBUG_PRINT ("error during writing error-page\n");
					close(cfd); 
					exit(1);
				}
				
				close(cfd);
				
				exit(0);
			} 
	 
			if(write_page(cfd, path) == -1){
				DEBUG_PRINT ("error during writing page\n");
				exit(1);
			}
		
			close(fd);
			close(cfd);
			
			exit(0);
		}else 
			close(cfd);
	}

	return 0;
}
