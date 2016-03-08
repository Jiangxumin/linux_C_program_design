#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

int output(char *file_name)
{
	FILE *fp;
	char buf[MAX];	
	static int count = 0;
	int n;

	fp = fopen(file_name, "r");
	if(fp == NULL){
		perror("fail to open");
		return -1;		
	}
	
	while(fgets(buf, MAX, fp) != NULL){
		n = strlen(buf);
		buf[n - 1] = '\0';

		printf("%s\n", buf); 

		if(count++ % 5 == 0)
			printf("\n");
	}

	fclose(fp);
	
	return 0;
}

int main(void)
{
	char file_name[][10] = {"test.txt", 
					"test1.txt",
					"test2.txt"
					};
	int i;
	
	i = 0;
	while(i < 3){
		if(output(file_name[i]) == -1)
			exit(1);
		i++;
	}

	return 0;
}
