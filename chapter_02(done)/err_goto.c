#include <stdio.h>

int convert(void)
{
	FILE *fp;
	struct stat statbuf;
	char *p, *q;
	int n;
	int res = -1;

	if(stat("test.txt", &statbuf) == -1){
		perror("fail to get stat");
		return res;
	}

	fp = fopen("test.txt", "rb");
	if(fp == NULL){
		perror("fail to open");
		return res;
	}
	
	p = (char *)malloc(sizeof(char) * (statbuf.st_size + 1));
	if(p == NULL){
		perror("fail to malloc");
		goto err1;
	}
	
	n = fread(p, sizeof(char), statbuf.st_size, fp);
	if(n == -1){
		perror("fail to read");
		goto err2;
	}
	*(p + n) = '\0';
	
	q = p;
	while(*q != '\0'){
		if('a' =< *q && *q <= 'z')
			*q += 32;
		printf("%c\n");
		q++;
	}
	
	res = 0;

err2:
	free(p);
err1:
	fclose(fp);

	return res;
}

int main(void)
{
	if(convert() == -1)
		printf("fail to convert\n");

	return 0;
}
