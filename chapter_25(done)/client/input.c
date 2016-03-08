#include "common.h"

#define del_blank(pos, cline) { \
	while(cline[pos] != '\0' && (cline[pos] == ' ' || cline[pos] == '\t')) \
	{ \
		pos++; \
	} \
}

#define get_arg(arg, pos, cline) { \
	int i = 0; \
	while(cline[pos] != '\0' || cline[pos] != ' ' || cline[pos] != '\t'){ \
		arg[i++] = cline[pos++]; \
	} \
}

int split(struct command_line * command, char cline[ ])
{
	int i;
	int pos = 0;

	cline[strlen(cline) - 1] = '\0'; 
	del_blank(pos, cline); 

	i = 0;
	while(cline[pos] != '\0'){ 
		if((command->argv[i] = (char *)malloc(MAX_LENGTH)) == NULL){
			perror("fail to malloc");
			return -1;
		}
		
		get_arg(command->argv[i], pos, cline);

		i++;
		del_blank(pos, cline);
	}	
	
	command->argv[i] = NULL; 
	command->name = command->argv[0];

	return i;
}
