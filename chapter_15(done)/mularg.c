#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct arg_struct ARG;

struct arg_struct{
	char arg1[10];
	int arg2;
	float arg3;
};

void * thfn(void * arg)
{
	ARG * p = (ARG *)arg; 			
	printf("arg1 is : %s, arg2 is : %d, arg3 is : %f\n", p->arg1, p->arg2, p->arg3); 

	return NULL;
}

int main(int argc, char *argv[ ])
{
	pthread_t tid;
	ARG arg; 											
	int err;
	
	strcpy(arg.arg1, argv[1]);
	arg.arg2 = atoi(argv[2]);
	arg.arg3 = atof(argv[3]);
	
	err = pthread_create(&tid, NULL, thfn, (void *)&arg); 				
	if(err != 0){
		printf("can¡¯t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	return 0;
}
