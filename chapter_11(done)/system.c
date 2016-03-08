#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX 1024

int main(void)
{
	int fd;
	char buf[MAX];
	int n;

	if(system("ls > temp.txt") == -1){
		perror("fail to exec command");
		exit(1);
	}

	if(fd = open("temp.txt", O_RDWR) == -1){
		perror("fail to open");
		exit(1);
	}

	if((n = read(fd, buf, MAX)) == -1){
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0';

	printf("%s", buf);
	
	return 0;
}
