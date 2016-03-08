#include <stdio.h>

int add(int a, int b)
{
	return a + b; 
}

int main(void)
{
	int array[5]; 
	int i;

	while(i < 5){
		int res; 

		res = add(i, 1); 
		array[i] = res; 
	}
	
	for(i = 0; i < 10; i++)
		printf("array[%d] : %d\n", i + 1, array[i]); 

	return 0;
}
