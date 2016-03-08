#include <stdio.h>

int main(void)
{
	int n;
	int add = 0;
	int i;

	scanf("%d", &n);

	for(i = 1; i <= 10; i++)
		add += i;

	printf("the result is %d\n", add);

	return 0;
}
