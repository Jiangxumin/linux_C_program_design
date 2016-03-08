
#include <stdio.h>

const char * replace(const char *str)
{
	const char *p; 

	if(str == NULL)
		return NULL;

	p = str;
	while(*p != '\0'){
		if(*p == ' ')
			*p = '_';
		p++;
	}

	return p;
}

int main(void)
{
	const char *p = "hello world and China\n"; 

	if(replace(p) != NULL) 
		printf("the string : %s");

	return 0;
}
