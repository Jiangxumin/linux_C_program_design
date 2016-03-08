#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/* SIGBUS信号的处理函数，输出一行提示信息 */
void sigbus_handler(int signo)
{
	printf("permission denied\n");
}

int main(void)
{
	int fd;
	char *buf;
	struct stat statbuf;

	if(signal(SIGBUS, sigbus_handler) == SIG_ERR){ /* 设置SIGBUS的信号处理程序 */
		perror("can’t set handler for SIGALRM");
		exit(0);
	}

	if(stat("test.txt", &statbuf) == -1){ /* 得到一个文件的状态信息，得到文件的大小 */
		perror("fail to get stat");
		exit(1);
	}

	fd = open("test.txt", O_WRONLY); /* 以可写方式打开文件 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}

	/* 建立一个内存映射区，其访问权限为只读 */
	buf = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if(buf == MAP_FAILED){
		perror("fail to mmap");
		exit(1);
	}
	
	printf("try to write\n");
	strcpy(buf, "China\n"); /* 尝试写一个只读的映射区 */

	/* 将映射区的访问权限改变为可读可写 */
	if(mprotect(buf, statbuf.st_size, PROT_READ | PROT_WRITE) == -1){
		perror("fail to alter permission");
		exit(1);
	}

	printf("write again\n");
	strcpy(buf, "China\n"); /* 再次写一个只读的映射区 */

	if(munmap(buf, statbuf.st_size) == -1){ /* 撤销内存映射 */
		perror("fail to munmap");
		exit(1);
	}

	close(fd); /* 关闭文件 */
	
	return 0;
}
