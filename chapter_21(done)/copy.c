#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[ ])
{
	FILE *fp1, *fp2; 
	int c;

	if(argc != 3){
		printf("wrong command\n");
		exit(1);
	}
	
	if((fp1 = fopen(argv[1], "rb")) == NULL){ 
		perror("fail to open");
		exit(1);
	}
	if((fp1 = fopen(argv[2], "wb")) == NULL){
		perror("fail to open");
		exit(1);
	}
	
	while((c = fgetc(fp1)) != EOF){
		if(fputc(c, fp2) == EOF){ 
			perror("fail to write");
			exit(1);
		}
		if(fputc(c, STDOUT_FILENO) == EOF){
			perror("fail to write");
			exit(1);
		}
	}

	if(errno != 0){ 
		perror("fail to read");
		exit(1);
	}

	fclose(fp1); 
	fclose(fp2);

	return 0;
}
