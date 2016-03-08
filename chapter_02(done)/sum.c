#include <stdio.h>

int main(void)
{
	int i;
	int sum;
	int n;

	scanf("%d", &n);

	sum = 0;
	for(i = 1; i <= n; i++)
		sum += i;

	printf("the result is : %d\n", sum);

	return 0;
}
