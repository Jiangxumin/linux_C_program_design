#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main(void)
{
	pid_t pid;
	struct rusage rusage;

	pid = fork();

	if(pid < 0){
		printf("fail to fork\n");
		exit(0);
	}else if(pid == 0){
		printf("the child\n");
		
		exit(0);
	}else
		printf("the parent\n");
	
	if(wait3(NULL, 0, &rusage) == -1){
		perror("fail to wait");
		exit(1);
	}

	printf("utime is %d", rusage.ru_utime);
	printf("stime is %d", rusage.ru_stime);
	printf("maxrss is %d", rusage.ru_maxrss); 
	printf("ixrss is %d", rusage.ru_ixrss); 
	printf("idrss is %d", rusage.ru_idrss);
	printf("isrss is %d", rusage.ru_isrss);
	printf("minflt is %d", rusage.ru_minflt);
	printf("majflt is %d", rusage.ru_majflt);
	printf("nswap is %d", rusage.ru_nswap);
	printf("inblock is %d", rusage.ru_inblock);
	printf("oublock is %d", rusage.ru_oublock);
	printf("msgsnd is %d", rusage.ru_msgsnd);
	printf("msgrcv is %d", rusage.ru_msgrcv);
	printf("nsignals is %d", rusage.ru_nsignals);
	printf("nvcsw is %d", rusage.ru_nvcsw);
	printf("nivcsw is %d", rusage.ru_nivcsw);

	return 0;
}
