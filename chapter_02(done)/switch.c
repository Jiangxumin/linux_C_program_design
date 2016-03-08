#include <stdio.h>

int main(void)
{
	char score;
	
	scanf("%c", &score);

	switch(score){
	case 'A': 
		printf("excellent\n");
		break;
	case 'B': 
		printf("good\n");
		break;
	case 'C': 
		printf("pass\n");
		break;
	default: 
		printf("fail\n");
	}

	return 0;
}
