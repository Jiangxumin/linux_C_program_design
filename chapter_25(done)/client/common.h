#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include "iolib.h"

#define MAX_LINE 1024
#define PORT 8000 
#define COMMAND_LINE 256
#define MAX_ARG 10 
#define MAX_LENGTH 64 
#define NAME_LEN 256 

struct command_line{
	char *name;
	char *argv[MAX_ARG];
};

extern int split(struct command_line *command, char cline[]);

extern int do_connect(char *ip,struct sockaddr_in *sin, int *sock_fd); 
extern int do_get(const char *src, const char *dst, int sock_fd);
extern int do_put(const char *src, const char *dst, int sock_fd);
extern int do_serv_cd(char *path, int sock_fd); 
extern int do_serv_ls(char *path, int sock_fd); 
extern int do_cd(char * path);
extern int do_ls(char *path);
extern int do_bye(int sock_fd);
