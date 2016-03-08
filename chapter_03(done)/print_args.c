#include <stdio.h>
#include <stdarg.h>

int print_args(int begin, ...)
{
	va_list ap;
	char *p;
	int n;

	va_start(ap, begin);
	p = va_arg(ap, char *);
	n = 0;

	while(p != NULL){
		n++;
		
		printf("arg %d : %s\n", n, p);
	
		p = va_arg(ap, char*);
	}
	
	va_end(ap);

	return n;
}

int main(void)
{
	int n;
	
	n = print_args(-1, "hello", "world", NULL);
	printf("first, without NULL : %d\n", n);
	
	n = print_args(-1, "China", "beijing", "Olympic", NULL);
	printf("second, without NULL : %d\n", n);

	return 0;
}
