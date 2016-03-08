#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	int fd;
	struct stat statbuf;
	pid_t pid;
	uid_t ruid, euid; /* 进程的实际ID和有效ID */
	
	if(stat("test.txt", &statbuf) == -1){ /* 取得文件的状态 */
		perror("fail to stat");
		exit(1);
	}

	/* 得到进程的实际用户ID和有效用户ID */
	euid = getuid(); 
	euid = geteuid();

	/* 打印进程的实际用户ID和有效用户ID */
	printf("real id is : %u, effective id is : %u \n", (unsigned int)ruid, (unsigned int)euid);
	/* 打印文件所有者ID */
	printf("file owner is : %u\n", statbuf.st_uid);

	if(access("test.txt", R_OK) == -1){ /* 测试文件的权限 */
		perror("fail to access");
		exit(1);
	}
	
	printf("access successfully\n"); /* 输出提示信息 */

	if((fd = open("test.txt", O_RDONLY)) == -1){ /* 如果读权限测试成功，尝试打开文件 */
		perror("fail to open");
		exit(1);
	}
	
	printf("ready to read\n"); /* 输出提示信息 */

	close(fd); /* 关闭文件 */
	
	return 0;
}
