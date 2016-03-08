#include <stdio.h>

int main(void)
{
	printf("the begin\n");

	goto end;

	printf("hello world\n");

end:
	printf("the end\n");

	return 0;
}
