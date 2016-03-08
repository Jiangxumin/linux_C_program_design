#include <stdio.h>

#define MAX 5
int array[MAX] = {2,7,6,4,8, };

int sum()
{
	int i;
	int n;

	n = 0;
	for(i = 0; i < MAX; i++)
		n += array[i];

	return n;
}

int get_max()
{
	int max;
	int i;
	
	i = 0;
	max = array[i];
	for(i = 0; i < MAX; i ++) 
		if(array[i] > max)
			max = array[i];

	return max;
}


void print()
{
	int i; 

	for(i = 0; i < MAX; i++)
		printf("array[%d] : %d\n", i + 1, array[i]);
}
