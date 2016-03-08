#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( void ){
	time_t cur_time;
	
	
	if ((cur_time = time (NULL)) == -1 ){
		perror ("time");
		exit (1);
	}
	
	printf ("the current time is : %d \n", cur_time);
	
	exit(0);
}
