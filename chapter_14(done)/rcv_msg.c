#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 4096

struct msg{   
	long msg_types;  
	char msg_buf[511]; 
};

int main( int argc, char * argv[] ) {
	int		qid;
	int 		len;
	struct msg pmsg;

	if ( argc != 2 ){ 
		perror ( "USAGE: read_msg <queue ID>" );
		exit ( 1 );
	}
	
	qid = atoi ( argv[1] );   

	len = msgrcv ( qid, &pmsg, BUFSZ, 0, 0 );
	
	if ( len > 0 ){
		pmsg.msg_buf[len] = '\0';  
		printf ("reading queue id :%05ld\n", qid ); 
		printf ("message type : %05ld\n", pmsg.msg_types ); 
		printf ("message length : %d bytes\n", len ); 
		printf ("mesage text: %s\n", pmsg.msg_buf);  
	}
	else if ( len == 0 )
		printf ("have no message from queue %d\n", qid );
	else {
		perror ( "msgrcv");
		exit (1);
	}
	system("ipcs -q")	
	exit ( 0 ) ;
}
