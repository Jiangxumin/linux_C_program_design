
#include "common.h"

int main(void)
{
     struct sockaddr_in sin; 
     struct sockaddr_in cin; 
     int lfd, cfd;
     socklen_t len = sizeof(struct sockaddr_in); 

     char buf[MAX_LINE];
     char str[ADDR_LEN]; 
     int sock_opt = 1;
     int n; 
	pid_t pid; 
    	
	if(init(&sin, &lfd, sock_opt) == -1) 
		exit(1);
	
	printf("waiting connections ...\n");
     
     while(1){ 
         if( (cfd = accept(lfd, (struct sockaddr *)&cin, &len)) == -1){ 
			perror("fail to accept");
	       	exit(1);
	  	}

		if( (pid = fork()) < 0){
			perror("fail to fork");
			exit(1);
		}else if(pid == 0){ 
			close(lfd); 
			
			while(1){ 
				if(my_read(cfd, buf, MAX_LINE) == -1) 
					exit(1);

	  			if(strstr(buf, "GET") == buf)
	       				if(do_put(cfd, &buf[4]) == -1)
						printf("error occours while putting\n");
	  			else if(strstr(buf, "PUT") == buf)
					if(do_get(cfd, &buf[4]) == -1) 
						printf("error occours while getting\n");
				else if(strstr(buf, "CD") == buf) 
					if(do_cd(cfd, &buf[4]) == -1)
						printf("error occours while changing directory\n");
				else if(strstr(buf, "LS") == buf)
					if(do_ls(cfd, &buf[4]) == -1)
						printf("error occours while listing\n");
				else if(strstr(buf, "BYE") == buf) 
					break; 
				else{ 
					printf("wrong command\n");
					exit(1);
				}
			}
	  
			close(cfd);
	
			exit(0);
     	}else
			close(cfd);
   	}
	
  	return 0; 
}
