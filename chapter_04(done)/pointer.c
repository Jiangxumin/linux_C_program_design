#include <stdio.h>

struct test{
	int array[2];
	char ch;
};

typedef struct test Test;

int main(void)
{
	Test var = {0x12345678, 0x12345678, 0x30};
	char *p;

	p = (char *)&var;
	printf("1 byte : 0x%d\n", *p);

	p = (short *)p;
	printf("2 bytes : 0x%d\n", *p);

	p = (int *)p;
	printf("4 bytes : 0x%d\n", *p);

	p = (long long *)p;
	printf("8 bytes : 0x%d\n", *p);

	p = (Test *)p;
	printf("whole bytes : 0x%d, 0x%d, %c", p->array[0], p->array[1], p->ch);

	return 0;
}
