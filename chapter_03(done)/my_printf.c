#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAX 64

char * itoa(int n, char *p)
{
	char *q;

	if(p == NULL)
		return NULL;

	p[0] = (n / 10000) + '0';
	n = n % 10000;
	p[1] = (n / 1000) + '0';
	n = n % 1000;
	p[2] = (n / 100) + '0';
	n = n % 100;
	p[3] = (n / 10) + '0';
	n = n % 10;
	p[4] = n + '0';
	p[5] = '\0';
	
	q = p;
	while(*q != '\0' && *q != '0')
		q++;
	
	if(*q == '\0')
		return p;
	strcpy(p, q);

	return p;
}

int my_printf(const char *format, ...)
{
	va_list ap;
	char c, ch;
	int i;
	char *p;
	int n = 0;
	char buf[MAX];

	va_start(ap, format); 

	c = *format;
	while(c != '\0'){
		if(c == '%'){
			format++; 
			c = *format;
			
			switch(c){
			case 'c': 
				ch = va_arg(ap, int); 
				putchar(ch); 
				n++;
				break;

			case 'd':
				i = va_arg(ap, int); 
				itoa(i, buf); 
				n += strlen(buf); 
				fputs(buf, stdout); 
				break;

			case 's': 
				p = va_arg(ap, char *);
				n += strlen(p);
				fputs(p, stdout); 
			}
		}else{
			putchar(c); 
			n++;
		}
		
		format++; 
		c = *format;
	}
	
	va_end(ap); 

	return n; 
}

int main(void)
{
	my_printf("the char is : %c\n, the number is : %d\n, the string is : %s\n", 'a', 100, "hello world\n"); 
	
	return 0;
}
