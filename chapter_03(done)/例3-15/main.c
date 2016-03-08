#include <stdio.h>

extern int array[ ];
extern int sum();
extern int get_max();
extern void print();

int main(void)
{
	int all, max;

	all = sum();
	max = get_max();
	print();
	printf("the sum : %d, the max : %d\n", all, max);

	return 0;
}
