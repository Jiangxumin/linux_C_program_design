#include <stdio.h>

int main(void)
{
	int n;
	int mul = 1;
	int i;
	int t;

	scanf("%d", &n);

	i = 1;
	t = i <= n;
	if(t == 0)
		goto done;
loop:
	mul *= i;
	i++;
	t = i <= n;
	if(t == 1)
		goto loop;

done:
	printf("the result is %d\n", mul);

	return 0;
}
