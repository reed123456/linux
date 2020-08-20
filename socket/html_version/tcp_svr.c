#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

int tcp_create() {
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	int op = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if ( r == -1 ) perror("bind"),exit(1);

	r = listen(lfd, SOMAXCONN);
	if ( r == -1 ) perror("listen"),exit(1);

	return lfd;
}

void handler(int s) {
	while ( waitpid(-1, NULL, WNOHANG) > 0 )
	  ;
}

ssize_t read_line(int cfd, char *buf, size_t len) {
	int i = -1;

	for (i=0; i<len-1; i++) {
		int r = read(cfd, &buf[i], 1);
		if ( r == 0 ) break;
		if ( buf[i] == '\n' ) break;
	}

	buf[++i] = '\0';

	return i;
}

void do_res(int cfd, char *buf) {
	// GET /index.html HTTP/1.1\r\n
	 char tmp1[1024];
	 char filename[1024];
	 sscanf(buf, "%s /%s", tmp1, filename);
	 printf("file=[%s]\n", filename);
	 int fd = open(filename, O_RDONLY);
	 if ( fd == -1 ) {
		 char *msg = "404 page not found";
	 	write(cfd, msg, strlen(msg));
	 return;
	 }
	
	 while ( 1 ) {
		 char tmp[1024];
	 	memset(tmp, 0x00, sizeof(tmp));
	 	int r = read(fd, tmp, 1023);
	 	if ( r <= 0 ) break;
	 		write(cfd, tmp, r);
	}
	
	 close(fd);	
}

void exec_web(int cfd) {
	char buf[1024];
	char *res = "HTTP/1.1 200 OK\r\n\r\n";
	write(cfd, res, strlen(res));
	while ( 1 ) {
		int r = read_line(cfd, buf, 1024);
		if ( r <= 2 ) break;
		printf("r=%d, buf=[%s]\n", r, buf);
		if ( strncasecmp(buf, "GET", 3) == 0 ) {
			do_res(cfd, buf);
		}
	}
}

int main( void ) {
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	int lfd = tcp_create();

	for ( ; ; ) {
		int cfd = accept(lfd, NULL, NULL);
		if ( cfd == -1 ) continue;
		pid_t pid = fork();
		if ( pid == 0 ) {
			close(lfd);
			exec_web(cfd);
			close(cfd);
			exit(0);
		} else {
			close(cfd);
		}
	}
}

