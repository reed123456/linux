#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
	long channel;
	char buf[100];
};

int main( void ) {
	int id = msgget(1234, 0);
	struct msgbuf mb;

	long c;
	memset(&mb, 0x00, sizeof(mb));
	printf("你想读取哪个通道的数据:");
	scanf("%ld", &c);
	msgrcv(id, &mb, 100, c, 0);
	printf("%s\n", mb.buf);
}

