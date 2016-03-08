#include <stdio.h>

int main(void)
{
	int n;
	int mul = 1;
	int i;

	scanf("%d", &n);
	
	i = 1;
	while(i <= n){
		mul *= i;
		i++;
	}

	printf("the result is %d\n", mul);

	return 0;
}
