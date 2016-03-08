#include "common.h"

int insert_struct(Book *pos, int id, char * name)
{
	Book p;

	p = (Book)malloc(sizeof(struct book));
	if(p == NULL){
		perror("fail to malloc");
		return -1;
	}

	p->id = id;
	strcpy(p->name, name); 

	*pos = p; 
	
	return 0;
}

int insert_int(int **pos, int val)
{
	int *p;
	
	p = (int *)malloc(sizeof(int)); 

	*p = val; 
	*pos = p; 
	
	return 0;
}
