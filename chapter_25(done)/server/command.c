#include "common.h"

int init(struct sockaddr_in *sin, int *lfd, int sock_opt)
{
	int tfd;
	
	bzero(sin, sizeof(struct sockaddr_in));
     sin->sin_family = AF_INET;
     sin->sin_addr.s_addr = INADDR_ANY;
     sin->sin_port = htons(PORT);
    
     if( (tfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
          perror("fail to creat socket");
          return -1;
     }
     
	setsockopt(tfd, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof(int));

   
     if( (bind(tfd, (struct sockaddr *)sin, sizeof(struct sockaddr_in))) == -1){
          perror("fail to bind");
          return -1;
     }
	
     if( (listen(tfd, 20)) == -1){
          perror("fail to listen");
	  return -1;
     }
	
	*lfd = tfd;

	return 0;

}


int do_put(int cfd, char *file)
{
     struct stat statbuf; 
     int n, fd;
	int res = -1; 
	char buf[1024];
     
	if( (fd = open(file, O_RDONLY)) == -1){ 
	  	my_write(cfd, "ERR open server file\n", strlen("ERR open server file\n"));  
		
		return res; /* 返回-1 */
	}

 	if( (fstat(fd, &statbuf)) == -1){ 
	  	my_write(cfd, "ERR stat server file\n", strlen("ERR stat server file\n"));
		goto end;
     	}
     
	if(!S_ISREG(statbuf.st_mode)){
	  	if(my_write(cfd, "ERR server path should be a regular file\n",
		 	strlen("ERR server path should be a regular file\n")) == -1)
			goto end;
		
		res = 0; 
		goto end;
     }
	
     sprintf(buf, "OK %d", statbuf.st_size); 
     if(my_write(cfd, buf, strlen(buf)) == -1) 
		goto end;
     if ( (my_read(cfd, buf, MAX_LINE)) <= 0)
		goto end;
     
	while(1){ 
	 	n = read(fd, buf, MAX_LINE); 

		if(n > 0)
	       		if(my_write(cfd, buf, n) == -1) 
				goto end;
	  	else if(n == 0) { 
	       	printf("OK\n");  
	       	break;
	  	}else	{ 
	  		perror("fail to read");
			goto end;	 
		}
    	}
	res = 0; 
end:
     close(fd); 
	return res;
}

int do_get(int cfd, char *file)
{
     struct stat statbuf; /* 文件状态缓冲区 */
     int n, fd;
	int res = -1;
		char buf[1024];
	int len;
 
	if( (fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1){ 
		if(errno == EISDIR){
	       	if(my_write(cfd, "ERR server has a dir with the same name\n",
		     	strlen("ERR server has a dir with the same name\n")) == -1) 
				goto end;
              
			res = 0; 
			goto end;
		}else{
	       	my_write(cfd, "ERR open server file\n", strlen("ERR open server file\n")); 
			goto end;
          }
	}
	
	if( (fstat(fd, &statbuf)) == -1){ 
	  	my_write(cfd, "ERR stat server file\n", strlen("ERR stat server file\n")); 
	  	goto end;
     }

	len = statbuf.st_size;
     
	if(!S_ISREG(statbuf.st_mode)){ 
	  	if(my_write(cfd, "ERR server path should be a regular file\n",
			strlen("ERR server path should be a regular file\n")) == -1)
			goto end;
		
		res = 0;
		goto end;
     }
     
	if(my_write(cfd, "OK", 2) == -1) 
		goto end;

     while(1){
	  	n = my_read(cfd, buf, MAX_LINE);
	  	
		if(n > 0){
	       	write(fd, buf, n);
	       	len -= n;
	  	}else if(len == 0) {
		    	printf("OK\n");
	       		break;
	  	}else
	      		goto end;
     }
	
	res = 0;
end:
     close(fd); 

	return res;
}

int do_cd(int cfd, char *path)
{
	if(chdir(path) == -1){ 
		perror("fail to change directory\n");
		my_write(cfd, "ERR can't change directory\n", strlen("ERR can't change directory\n"));
	  	
		return -1;
	}

	my_write(cfd, "OK\n", strlen("OK\n"));
	
	return 0;
}

int do_ls(int cfd, char *path)
{
	char cmd[128];
	char buf[NAME_LEN];
	struct stat statbuf; 
    	int n, fd;
	int res = -1;

	sprintf(cmd, "ls %s > temp.txt ",path);
	system(cmd);

	if( (fd = open("temp.txt", O_RDONLY)) == -1){ 
	  	my_write(cfd, "ERR ls server file\n", strlen("ERR ls server file\n"));  
		return res;
	}

 	if( (fstat(fd, &statbuf)) == -1){
	  	my_write(cfd, "ERR stat server file\n", strlen("ERR stat server file\n"));
		goto end;
     }

     if(!S_ISREG(statbuf.st_mode)){
	  	if(my_write(cfd, "ERR server path should be a regular file\n",
		 	strlen("ERR server path should be a regular file\n")) == -1)
			goto end;
		res = 0;
		goto end;
     }
	
     sprintf(buf, "OK %d", statbuf.st_size); 
     if(my_write(cfd, buf, strlen(buf)) == -1) 
		goto end;
     
     if ( (my_read(cfd, buf, MAX_LINE)) <= 0)
		goto end;
     
	while(1){
	 	n = read(fd, buf, MAX_LINE); 
	  	if(n > 0)
	       	if(my_write(cfd, buf, n) == -1) 
				goto end;
	  	else if(n == 0) { 
	       	printf("OK\n"); 
	       	break;
	  	}else	{ 
	  		perror("fail to read");
			goto end;	 
		}
    	}

	res = 0;
end:
     close(fd); 
	
	return res;
}
