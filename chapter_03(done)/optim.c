#include <stdio.h>

int count = 0; 

int func(int a)
{
	count++; 
	return a + 1; 
}

int main(void)
{
	int res;

	res = 4 * func(1); 
	
	printf("the count : %d\n", count); 
	printf("the result : %d\n", res);

	return 0;

}
