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
	sigset_t sig_pend;

	sigemptyset(&set);
	sigemptyset(&sig_pend);
	
	if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){
		perror("can¡¯t set handler for SIGUSR1");
		exit(1);
	}
	
	sigaddset(&set, SIGUSR1 - 1); 
	
	if(sigprocmask(SIG_BLOCK, &set, NULL) == -1){ 
		perror("fail to set signal-mask");
		exit(1);
	}
	
	sleep(10); 

	if(sigpending(&sig_pend) == -1){  
		perror("fail to get pending signal");
		exit(1);
	}
	
	if(sigismember(&sig_pend, SIGUSR1 - 1) == 1) 
		printf("there is a signal, SIGUSR1, is pending\n");
	else{
		perror("fail to test signal-set");
		exit(1);
	}
	
	if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){ 
		perror("fail to set signal-mask");
		exit(1);
	}
	
	printf("SIGUSR1 is available again\n");

	return 0;
}
