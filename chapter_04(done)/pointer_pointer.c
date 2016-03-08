#include <stdio.h>

int main(void)
{
	int a;
	int *p;
	int **q;

	a = 100;
	p = & a;
	q = &p;

	printf("var a : %d\n", a);
	printf("pointer p : 0x%x\n", *p);
	printf("pointer pointer q : 0x%x\n", *q);

	return 0;
}
