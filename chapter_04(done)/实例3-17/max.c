#include "common.h"

void *max(void *array[], int len, cmp func)
{
	int i;
	void *tmp;

	tmp = array[0]; 
	for(i = 1; i < len; i++) { 
		if((*func)(tmp, array [i]) == -1)
			tmp = array [i];
	}
	
	return tmp;
}
