#include <stdio.h>

struct test{  
	int array[5];
	int a;
	int *p;
};  

int main(void)
{	
	struct test var;  
	int i;

	 
	for(i = 0; i < 5; i++)
		printf("array [%d] : 0x%x\n", i + 1, &(var.array[i]));  
	printf("a : 0x%x\n", &(var.a));  
	printf("p : 0x%x\n", &(var.p));  

	return 0;
}
