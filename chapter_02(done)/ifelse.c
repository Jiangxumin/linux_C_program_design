#include <stdio.h>

int main(void)
{
	int a, b;

	scanf("%d%d", &a, &b);

	if(a > b)
		printf("a is higher than b\n");
	else
		printf("a is lower than b\n");

	return 0;
}
