#include <stdio.h>

int main(void)
{	
	printf("stdin is ");
	if(stdin->_flags & _IO_UNBUFFERED) 
		printf("unbuffered\n");
	else if(stdin->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size is %d\n", stdin->_IO_buf_end - stdin->_IO_buf_base);
	printf("discriptor is %d\n\n", fileno(stdin)); 
	
	printf("stdout is ");
	if(stdout->_flags & _IO_UNBUFFERED)
		printf("unbuffered\n");
	else if(stdout->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size is %d\n", stdout->_IO_buf_end - stdout->_IO_buf_base); 
	printf("discriptor is %d\n\n", fileno(stdout)); 
	
	printf("stderr is ");
	if(stderr->_flags & _IO_UNBUFFERED) 
		printf("unbuffered\n");
	else if(stderr->_flags & _IO_LINE_BUF)
		printf("line-buffered\n");
	else
		printf("fully-buffered\n");
	printf("buffer size is %d\n", stderr->_IO_buf_end - stderr->_IO_buf_base); 
	printf("discriptor is %d\n\n", fileno(stderr)); 

	return 0;
}
