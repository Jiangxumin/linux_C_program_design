#include <stdio.h>

int main(void)
{
	int a, b;
	int t;

	scanf("%d%d", &a, &b);

	t = a > b;
	if(t == 1)
		goto true;
	printf("a is lower than b\n");

	goto done;
true:
	printf("a is higher than b\n");

done:
	return 0;
}
