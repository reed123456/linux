#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

int tcp_init() {
	int lfd = socket(AF_INET, SOCK_STREAM, 0);

	int op = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	addr.sin_addr.s_addr =htonl(INADDR_ANY);
	int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( r == -1 ) perror("bind"),exit(1);

	listen(lfd, SOMAXCONN);

	return lfd;
}

void to_upper(char *s) {
	int i;
	for (i=0; s[i]!=0; i++)
	  if ( s[i]>='a' && s[i]<='z')
		s[i] = s[i] - 32;
}

void *process(void *arg) {
	int cfd = *(int*)arg;
	free(arg);

	char buf[100];
	while ( 1 ) {
		int r = read(cfd, buf, 100);
		if ( r <= 0 ) {
			printf("client close\n");
			break;
		}

		to_upper(buf);
		write(cfd, buf, r);
	}

	close(cfd);
}

int main( void ) {
	int lfd = tcp_init();

	for ( ; ; ) {
		int newfd = accept(lfd, NULL, NULL);
		pthread_t tid;
		int *p = malloc(sizeof(int));
		*p = newfd;
		pthread_create(&tid, NULL, process, p);
		pthread_detach(tid);
	}
}

