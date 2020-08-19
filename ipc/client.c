#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>

struct msgbuf {
	long type;
	char buf[100];
};


int main( void ) {
	int id = msgget(12345, 0);

	struct msgbuf mb;
	while ( fgets(mb.buf+sizeof(long), 100, stdin) != NULL ) {
		mb.type = 1;
		*(long*)mb.buf = getpid();
		msgsnd(id, &mb, 100, 0);
		struct msgbuf mb2;
		memset(&mb2, 0x00, sizeof(mb2));
		msgrcv(id, &mb2, 100, getpid(), 0);
		printf("=> %s\n", mb2.buf+sizeof(long));
	}
}

