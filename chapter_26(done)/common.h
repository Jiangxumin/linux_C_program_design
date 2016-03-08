#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "iolib.h"

#define MAX_LINE 1024 

#define BUG 1
#ifdef BUG
#define DEBUG_PRINT(str); 	printf(str);
#else
#define DEBUG_PRINT(str);
#endif

extern int init(struct sockaddr_in * sin, int * lfd, int * port, char *path);
extern int error_page(int sock_fd);
extern int get_path(int cfd, char * path);
extern int write_page(int cfd, char * path);
