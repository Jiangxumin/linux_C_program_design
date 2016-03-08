#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n");
}

int main(void)
{
	sigset_t set;
	
	if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){
		perror("can¡¯t set handler for SIGUSR1");
		exit(1);
	}

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1 - 1);

	if(sigprocmask(SIG_BLOCK, &set, NULL) == -1){
		perror("fail to set signal-mask");
		exit(1);
	}
	
	printf("SIGUSR1 is not available\n");

	sleep(10);

	if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){ 
		perror("fail to set signal-mask");
		exit(1);
	}

	printf("SIGUSR1 is available now\n");

	sleep(10);

	return 0;
}
