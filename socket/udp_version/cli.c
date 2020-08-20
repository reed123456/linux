#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main ( void ) {
	int sfd = socket(AF_INET, SOCK_DGRAM, 0);

	char buf[100];
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9898);
	inet_aton("127.0.0.1", &addr.sin_addr);
	socklen_t len = sizeof(addr);
	while (1) {
		memset(buf, 0x00, sizeof(buf));
		if (fgets(buf, 100, stdin) == NULL)
		  break;
		sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
		memset(buf, 0x00, sizeof(buf));
		recvfrom(sfd, buf, 100, 0, (struct sockaddr*)&addr, &len);
		printf("-> %s\n", buf);
	}
}
