#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void process(char *s) {
	int i;

	for (i=0; s[i]!='\0'; i++) {
		if ( s[i]>='a' && s[i]<='z' )
		  s[i] = s[i]-32;
	}
}
int main( void ) {
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if ( lfd == -1 ) perror("socket"),exit(1);
	printf("create socket ok\n");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("192.168.122.1", &addr.sin_addr);
	int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( r == -1 ) perror("bind"),exit(1);
	printf("bind ok\n");

	r = listen(lfd, SOMAXCONN);
	if ( r == -1 ) perror("listen"),exit(1);
	printf("listen ok\n");

	int newfd = accept(lfd, NULL, NULL);
	printf("有客户端链接上来\n");

	char buf[1024];
	while ( 1 ) {
		memset(buf, 0x00, sizeof(buf));
		r = read(newfd, buf, 1024);
		if ( r == 0 ) // 表示对方关闭
		  break;
		printf("r=%d, buf=%s\n", r, buf);
		process(buf);
		write(newfd, buf, r);
	}

	close(newfd);
	close(lfd);
}

