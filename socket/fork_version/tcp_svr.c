#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

int tcp_init(uint16_t port) {
	int lfd = socket(AF_INET, SOCK_STREAM, 0);

	int op = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( r == -1 ) perror("bind"),exit(1);

	listen(lfd, SOMAXCONN);

	return lfd;
}
void process(char *s) {
	int i;

	for (i=0; s[i]!='\0'; i++) {
		if ( s[i]>='a' && s[i] <='z' ) {
			s[i] = s[i] - 32;
		}
	}
}

void echo_client(int cfd) {
	char buf[1024];
	while ( 1 ) {
		memset(buf, 0x00, sizeof(buf));
		int r = read(cfd, buf, 1024);
		if ( r <= 0 )
		  break;
		process(buf);
		write(cfd, buf, strlen(buf));
	}
}
void handler(int s) {
	while ( waitpid(-1, NULL, WNOHANG) > 0 )
	  ;
}

int main( void ) {
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	int lfd = tcp_init(9999);

	for ( ; ; ) {
		int cfd = accept(lfd, NULL, NULL);
		if ( cfd == -1 ) continue;
		pid_t pid = fork();
		if ( pid == 0 ) {
			close(lfd);
			echo_client(cfd);
			exit(0);
		} else {
			close(cfd);
		}
	}
}

