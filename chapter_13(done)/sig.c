#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{
	switch(signo){
	case SIGUSR1:
		printf("Parent : catch SIGUSR1\n");
		break;
	case SIGUSR2:
		printf("Child : catch SIGUSR2\n");
		break;
	default:
		printf("should not be here\n");
		break;
	}

	return ;
}

int main(void)
{
	pid_t ppid, cpid;

	if(signal(SIGUSR1, handler) == SIG_ERR){
		perror("can¡¯t set handler for SIGUSR1");
		exit(1);
	}

	if(signal(SIGUSR2, handler) == SIG_ERR){
		perror("can¡¯t set handler for SIGUSR2");
		exit(1);
	}

	ppid = getpid();

	if((cpid = fork()) <0){
		perror("fail to fork");
		exit(1);
	}else if(cpid == 0){
		if(kill(ppid, SIGUSR1) == -1){
			perror("fail to send signal");
			exit(1);
		}

		while(1);
	}else{
		sleep(1);

		if(kill(cpid, SIGUSR2) == -1){
			perror("fail to send signal");
			exit(1);
		}

		printf("kill child\n");

		if(kill(cpid, SIGKILL) == -1){
			perror("fail to send signal");
			exit(1);
		}

		if(wait(NULL) == -1){
			perror("fail to wait");
			exit(1);
		}
	}

	return 0;
}
