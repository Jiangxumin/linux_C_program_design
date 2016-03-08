#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	pid = fork();

	if(pid < 0){
		printf("fail to fork\n");
		exit(0);
	}else if(pid == 0){
		printf("the child\n");
		
		sleep(5);
		
		printf("done\n");
		exit(0);
	}else
		printf("the parent\n");
	
	sleep(30);

	if(wait(NULL) == -1){
		perror("fail to wait");
		exit(1);
	}

	return 0;
}
