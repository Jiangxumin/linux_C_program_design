#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global;

int main(void)
{
	pid_t pid;
	int stack = 1;
	int * heap;
	
	heap = (int *)malloc(sizeof(int));
	*heap = 2;

	pid = vfork(); 

	if(pid < 0){
		printf("fail to fork\n");
		exit(1);	
	}else if(pid == 0){
		global++;
		stack++;
		(*heap)++;

		printf("data : %d, stack : %d, heap : %d\n", global, stack, *heap);
		printf("child terminates\n");

		exit(0);	
	}
	
	/* sleep(2); */

	printf("data : %d, stack : %d, heap : %d\n", global, stack, *heap);
	printf("parent terminates\n");
	
	return 0;
}
