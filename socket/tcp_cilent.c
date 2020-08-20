#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main( void ) {
	int cfd = socket(AF_INET, SOCK_STREAM, 0);

	// 服务器的ip和端口
	 struct sockaddr_in addr;
	 addr.sin_family = AF_INET;
	 addr.sin_port = htons(9999);
	 inet_aton("192.168.122.1", &addr.sin_addr);
	 int r = connect(cfd, (struct sockaddr*)&addr, sizeof(addr));
	 if ( r == -1 ) perror("connect"),exit(1);
	
	 char buf[1024];
	 while ( 1 ) {
	 memset(buf, 0x00, sizeof(buf));
	 if ( fgets(buf, 1024, stdin) == NULL )
	 break;
	 write(cfd, buf, strlen(buf));
	
	 memset(buf, 0x00, sizeof(buf));
	 if ( read(cfd, buf, 1024) == 0 ) {
	 printf("服务器关闭\n");
	 break;
	 }
	 printf("recv:%s\n", buf);
	 }

	 close(cfd);
}

