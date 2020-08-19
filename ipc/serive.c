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
int id;

void handler(int s) {
	msgctl(id, IPC_RMID, NULL);
	exit(0);
}

int main( void ) {
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);

	id = msgget(12345, IPC_CREAT|0644);

	struct msgbuf mb;

	while ( 1 ) {
		memset(&mb, 0x00, sizeof(mb));
		msgrcv(id, &mb, 100, 1, 0);
		mb.type = *(long*)(mb.buf);;
		msgsnd(id, &mb, 100, 0);
	}
}

