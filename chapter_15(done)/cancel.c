#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * tfn1(void * arg)
{
	printf("new thread\n"); 
	sleep(10); 
}

int main(void)
{
	pthread_t tid;
	void * res;
	int err;
	
	err = pthread_create(&tid, NULL, tfn1, NULL); 
	if(err != 0){
		printf("can¡¯t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_cancel(tid); 
	if(err != 0){
		printf("can¡¯t cancel thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_join(tid, res); 
	if(err != 0){
		printf("can¡¯t join thread %s\n", strerror(err));
		exit(1);	
	}
	
	if(res == PTHREAD_CANCELED)
		printf("thread %u has been canceled\n", (unsigned int)tid);
	else
		printf("error\n"); 

	return 0;
}
