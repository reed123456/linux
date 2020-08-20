#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

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

int main( void ) {
	int lfd = tcp_init();
	fd_set rset, allset;
	int i;
	int maxfd;
	int clients[FD_SETSIZE];
	for (i=0; i<FD_SETSIZE; i++)
	  clients[i] = -1;

	FD_ZERO(&rset);
	FD_ZERO(&allset);
	FD_SET(lfd, &allset);
	maxfd = lfd;

	for ( ; ; ) {
		rset = allset;
		int ready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if ( ready == -1 ) continue;
		if ( FD_ISSET(lfd, &rset) ) {
			int cfd = accept(lfd, NULL, NULL);
			for (i=0; i<FD_SETSIZE; i++)
			  if ( clients[i] == -1 )
				break;
			clients[i] = cfd;
			FD_SET(cfd, &allset);
			maxfd = (maxfd < cfd ? cfd : maxfd);
			if ( --ready <= 0 ) continue;
		}

		for (i=0; i<FD_SETSIZE; i++) {
			int cfd = clients[i];
			if ( cfd == -1 ) continue;
			if ( FD_ISSET(cfd, &rset) ) {
				char buf[1024] = {};
				int r = read(cfd, buf, 1024);
				if ( r <= 0 ) {
					clients[i] = -1;
					FD_CLR(cfd, &allset);
					close(cfd);
				}
				write(cfd, buf, r);
			}
		}
	}
}

