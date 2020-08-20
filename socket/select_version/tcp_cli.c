#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>

int main( void ) {
	int cfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	inet_aton("192.168.122.1", &addr.sin_addr);
	int r = connect(cfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( r == -1 ) perror("connect"),exit(1);

	fd_set rset;
	FD_ZERO(&rset);
	int stdno = fileno(stdin);
	int maxfd = cfd > stdno ? cfd : stdno;

	for ( ; ; ) {
		FD_SET(stdno, &rset);
		FD_SET(cfd, &rset);
		int ready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if ( FD_ISSET(stdno, &rset) ) {
			char buf[1024] = {};
			if ( fgets(buf, 1024, stdin) == NULL )
			  break;
			write(cfd, buf, strlen(buf));
		}
		if ( FD_ISSET(cfd, &rset) ) {
			char buf[1024] = {};
			if ( read(cfd, buf, 1024) <= 0 ) {
				printf("server close\n");
				break;
			}
			printf("%s", buf);
			fflush(stdout);
		}
	}
}

