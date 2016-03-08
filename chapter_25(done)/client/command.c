#include "common.h"

int do_connect(char *ip,struct sockaddr_in *sin, int *sock_fd)
{
	int sfd; 

	bzero(&sin, sizeof(struct sockaddr_in)); 
	sin->sin_family = AF_INET; 

	if(inet_pton(AF_INET, ip, &sin->sin_addr) == -1){
		perror("wrong format of ip address");
		return -1;
	}
    
	sin->sin_port = htons(PORT);
    	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ 
		perror("fail to creat socket");
		return -1;	
	}
	
	
    	if(connect(sfd, (struct sockaddr *)sin, sizeof(struct sockaddr_in)) == -1){
        	perror("fail to connect");
	   	return -1;
    	}
	
	*sock_fd = sfd; 
	
	return 0;
}

int do_get(const char *src, const char *dst, int sock_fd)
{
	char *dst_file; 
	char *p;
	struct stat statbuf; 
	int n, fd;
	char buf[MAX_LINE]; 
	int len;
	int res = -1; 
	
	if(src == NULL || dst == NULL){ 
		printf("wrong command\n"); 
		return -1;
	}
	
	if(src[strlen(src)-1]=='/'){
		printf("source file should be a regular file\n");
		return -1;
	}
	
   	if( (dst_file = (char *)malloc(strlen(dst) + strlen(src))) == NULL){ 
		perror("fail to malloc");
		return -1; 
	}
    
	strcpy(dst_file, dst); 
	if(dst_file[strlen(dst_file) - 1] != '/')
		strcat(dst_file, "/");
	p = rindex(src, '/'); 
    	strcat(dst_file, p + 1);  
	    	
	if((fd = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
	  	perror("fail to open dst-file");
	  	goto end2;
    	}
 
    	if(fstat(fd, &statbuf) == -1){ /* 取目标文件的文件状态 */
		perror("fail to stat dst-file");
	  	goto end1;
	}
	
	if(!S_ISREG(statbuf.st_mode)){
	  	printf("dst-file should be a regular file");
	  	goto end1;
	}

    	sprintf(buf, "GET %s", src); 
    	
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) 
		goto end1;
    	
	if( (n = my_read(sock_fd, buf, MAX_LINE)) <= 0){ 
		goto end1;
    	}
    	
	if(buf[0] == 'E'){ 
		write(STDOUT_FILENO, buf, n); 
	  	res = 0;
		goto end1;
    	}
    
    	len = atoi(&buf[3]);

	if(my_write(sock_fd, "RDY", 3) == -1)
		goto end1;
   
	while(1){
	 	n = my_read(sock_fd, buf, MAX_LINE);
	  	
		if(n > 0){
	    		write(fd, buf, n);
	       	len -= n;
	  	}else if(len == 0){
			printf("OK\n"); 
	       		break;
	  	}else 
			goto end1;
	}

	res = 0; 
end1:
    	free(dst_file); 
end2:       
	close(fd); 

	return res;
}

int do_serv_cd(char *path, int sock_fd)
{
	char buf[MAX_LINE];
	int n;
	
	sprintf(buf, "CD %s", path); 
     
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) 
		return -1;
     
	if( (n = my_read(sock_fd, buf, MAX_LINE)) <= 0) 
		return -1;
     
     	if(buf[0] == 'E') 
		write(STDOUT_FILENO, buf, n); 
	 
     	return 0;
}

int do_serv_ls(char *path, int sock_fd)
{
	char buf[MAX_LINE];
	int len;
	int n;
	
	sprintf(buf, "LS %s", path); 
     
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) 
		return -1;
     
	if( (n = my_read(sock_fd, buf, MAX_LINE)) <= 0)
		return -1;
     
     	if(buf[0] == 'E'){ 
		write(STDOUT_FILENO, buf, n);
	  	return 0;
     	}
     	len = atoi(&buf[3]); 
     
	if(my_write(sock_fd, "RDY", 3) == -1)
		return -1;
     
	while(1){ 
	 	n = my_read(sock_fd, buf, MAX_LINE); 
	  	
		if(n > 0){ 
	       		write(STDOUT_FILENO, buf, n);
	       		len -= n; 
	  	}else if(len == 0){ 
		    	printf("OK\n");
	       		break; 
	  	}else
			return -1;	       
	}

	return 0;
}

int do_bye(int sock_fd)
{
	char buf[MAX_LINE];
	
	sprintf(buf, "BYE");
    	if(my_write(sock_fd, buf, strlen(buf)+1) == -1)
		return -1;
     
	return 0;
}

int do_put(const char *src, const char *dst, int sock_fd)
{
	char *dst_file; 
	struct stat statbuf;
    	int n, fd; 
	int res = -1; 
	char buf[MAX_LINE];
	char *p;

	if(src == NULL || dst == NULL){ 
		printf("wrong command\n");
		return -1;
	}

	if(src[strlen(src)-1]=='/'){ 
	  	printf("source file should be a regular file\n");
	  	return -1;
    	}
     
	if((dst_file = malloc(strlen(dst)+strlen(src)+2)) == NULL){
		perror("fail to malloc");
		return -1;
	}
	
	strcpy(dst_file, dst);
    	if(dst_file[strlen(dst_file)-1] != '/')
		strcat(dst_file, "/");
	p = rindex(src, '/');
    	strcat(dst_file, p + 1);

	if((fd = open(src, O_RDONLY)) == -1){
	  	perror("fail to open src-file");
	  	goto end1;
    	}

 	if(fstat(fd, &statbuf) == -1){
	  	perror("fail to stat src-file");
	  	goto end2;
    	}
    
	if(!S_ISREG(statbuf.st_mode)){ 
		fputs("src-file should be a regular file\n", stderr);
	  	goto end2;
    	}
    
	sprintf(buf, "PUT %d %s", statbuf.st_size, dst_file);
	if(my_write(sock_fd, buf, strlen(buf)+1) == -1) 
		goto end2;
    
	if((my_read(sock_fd, buf, MAX_LINE)) <= 0) 
	  	goto end2;
     
     	if(buf[0]=='E'){ 
	  	write(STDOUT_FILENO, buf, n);
	 	goto end2;
     	}
     
     	while(1){ 
	  	n = read(fd, buf, MAX_LINE);
	  	
		if(n > 0)
	       		if(my_write(sock_fd, buf, n) == -1)
				goto end2;
	  	else if(n == 0){
	       		printf("OK\n");
	      		break;
	  	}else{ 
	       		perror("fail to read\n");
	       		goto end2;
	  	}
	}
    
	res = 0; 
end1:
	close(fd); 
end2:
	free(dst_file); 

	return res; 
}

int do_cd(char * path)
{
	if(chdir(path) == -1){ 
		perror("fail to change directory\n");
	  	return -1;
	}
	
	return 0;
}

int do_ls(char *path)
{	
	char cmd[128];
	char buf[NAME_LEN];
	FILE *fp;

	sprintf(cmd, "ls %s > temp.txt ",path);
	system(cmd);

	fp = fopen("temp.txt", "r");
	if(fp == NULL){
		perror("fail to ls");
		return -1;
	}

	while(fgets(buf, NAME_LEN, fp) == NULL)
		printf("%s", buf);

	fclose(fp);
	return 0;
}
