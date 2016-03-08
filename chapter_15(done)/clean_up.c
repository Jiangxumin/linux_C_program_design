#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void cleanup(void *arg)
{
	printf("No. %d clean-up procdure\n", *((int *)arg)); 
}

void *tfn1(void *arg)
{
	int a = 1;
	
	printf("the first thread \n");
	pthread_cleanup_push(cleanup, &a); 

	a = 2;

	pthread_cleanup_push(cleanup, &a); 

	return NULL; 

	pthread_cleanup_pop(0); 
	pthread_cleanup_pop(0);

	return NULL;
}

void *tfn2(void *arg)
{
	int a = 1;
	
	printf("the second thread \n");
	pthread_cleanup_push(cleanup, &a); 

	a = 2;

	pthread_cleanup_push(cleanup, &a); 

	pthread_exit(NULL); 

	pthread_cleanup_pop(0); 
	pthread_cleanup_pop (0);

	return NULL;
}

void *tfn3(void *arg)
{
	int a = 1;
	
	printf("the third thread \n");
	pthread_cleanup_push(cleanup, &a); 
	
	a = 2;

	pthread_cleanup_push(cleanup, &a); 
	pthread_cleanup_pop(1); 

	printf("ready to sleep\n");

	sleep(10); 

	pthread_cleanup_pop(0); 

	return NULL;
}

int main(void)
{
	pthread_t tid1, tid2, tid3, tid4;
	int err;
	
	err = pthread_create(&tid1, NULL, tfn1, NULL); 
	if(err != 0){
		printf("can¡¯t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_join(tid1, NULL); 
	if(err != 0){
		printf("can¡¯t join thread %s\n", strerror(err));
		exit(1);	
	}
 
	err = pthread_create(&tid2, NULL, tfn2, NULL); 
	if(err != 0){
		printf("can¡¯t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_join(tid2, NULL); 
	if(err != 0){
		printf("can¡¯t join thread %s\n", strerror(err));
		exit(1);	
	}

	err = pthread_create(&tid3, NULL, tfn3, NULL);
	if(err != 0){
		printf("can¡¯t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_cancel(tid3); 
	if(err != 0){
		printf("can¡¯t cancel thread %s\n", strerror(err));
		exit(1);	
	}

	err = pthread_join(tid3, NULL); 
	if(err != 0){
		printf("can¡¯t join thread %s\n", strerror(err));
		exit(1);	
	}
	
	return 0;
}
