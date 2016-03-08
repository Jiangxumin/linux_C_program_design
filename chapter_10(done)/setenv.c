#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char * p;
	
	p = getenv("HOME"); 
	if(p == NULL){
		perror("fail to putenv");
		exit(1);
	}
	printf("$HOME is %s\n", p); 
	
	if(setenv("HOME", "/home/admin", 0) == -1){ 
		perror("fail to putenv");
		exit(1);
	}
	
	p = getenv("HOME"); 
	if(p == NULL){
		perror("fail to putenv");
		exit(1);
	}
	printf("$HOME is %s \n", p); 

	if(setenv("HOME", "/home/admin", 1) == -1){ 
		perror("fail to putenv");
		exit(1);
	}

	p = getenv("HOME"); 
	if(p == NULL){
		perror("fail to putenv");
		exit(1);
	}
	printf("$ HOME is %s \n", p);

	return 0;
}
