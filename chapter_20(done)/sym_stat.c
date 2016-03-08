#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	struct stat buf; /* 存储文件状态信息 */
	
	if(stat("sl", &buf) == -1){
		perror("fail to stat");
	exit(1);
}
	
	printf("permission : %d\n", buf.st_mode); /* 打印文件权限字 */
	printf("inode number : %d\n", buf.st_ino); /* 打印i节点号 */
	printf("device number : %d\n", buf.st_dev); /* 打印文件系统设备号 */
	printf("r-device number : %d\n", buf.st_rdev); /* 打印硬件设备设备号 */
	printf("link : %d\n", buf.st_nlink); /* 打印硬链接数 */
	printf("uid : %d\n", buf.st_uid); /* 打印所有者用户ID */
	printf("gid : %d\n", buf.st_gid); /* 打印所有者组ID */
	printf("file size : %d\n", buf.st_size); /* 打印文件的大小 */
	printf("access time : %d\n", buf.st_atime); /* 打印最近一次的访问时间*/
	printf("motify time : %d\n", buf.st_mtime); /* 打印最近一次修改文件内容的时间 */
	printf("change time : %d\n", buf.st_ctime); /* 打印最近一次修改文件属性的时间 */
	printf("buf size : %d\n", buf.st_blksize); /* 打印最适的缓冲区大小 */
	printf("block size : %d\n", buf.st_blocks); /* 打印文件在外存上占用的盘块数 */

	if(stat("test.txt", &buf) == -1){
		perror("fail to stat");
	exit(1);
}

	printf("permission : %d\n", buf.st_mode); /* 打印文件权限字 */
	printf("inode number : %d\n", buf.st_ino); /* 打印i节点号 */
	printf("device number : %d\n", buf.st_dev); /* 打印文件系统设备号 */
	printf("r-device number : %d\n", buf.st_rdev); /* 打印硬件设备设备号 */
	printf("link : %d\n", buf.st_nlink); /* 打印硬链接数 */
	printf("uid : %d\n", buf.st_uid); /* 打印所有者用户ID */
	printf("gid : %d\n", buf.st_gid); /* 打印所有者组ID */
	printf("file size : %d\n", buf.st_size); /* 打印文件的大小 */
	printf("access time : %d\n", buf.st_atime); /* 打印最近一次的访问时间*/
	printf("motify time : %d\n", buf.st_mtime); /* 打印最近一次修改文件内容的时间 */
	printf("change time : %d\n", buf.st_ctime); /* 打印最近一次修改文件属性的时间 */
	printf("buf size : %d\n", buf.st_blksize); /* 打印最适的缓冲区大小 */
	printf("block size : %d\n", buf.st_blocks); /* 打印文件在外存上占用的盘块数 */
	
return 0;
}
