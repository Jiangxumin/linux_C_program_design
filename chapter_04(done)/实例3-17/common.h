#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*cmp)(void *, void *);

typedef struct book * Book;

struct book{
	int id;
	char name[10];
};

extern void *max(void *array[], int len, cmp func);

extern int cmp_int(void *p, void *q);
extern int cmp_struct(void *p, void *q);

extern int insert_struct(Book *pos, int id, char * name);
extern int insert_int(int **pos, int val);
