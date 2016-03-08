#include <stdio.h>

int main(void)
{
	int a = 31;
	int x = 0xFFFFFFFF;  

	printf("the first is : %d\n",  0xFFFFFFFF >> 31) ;  
	printf("the second is : %d\n",  x >> 31) ;  
	printf("the third is : %d\n",  0xFFFFFFFF >> a) ;

	return 0;
}
