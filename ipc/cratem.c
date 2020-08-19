#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main( void ) {
	int id = msgget(1234, IPC_CREAT|0644);
	if ( id == -1 ) perror("msgget"),exit(1);
	printf("msgget ok\n");
}
