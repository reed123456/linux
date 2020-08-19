#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( void ) {
	int fds[2];

	pipe(fds);

	pid_t pid = fork();
	if ( pid == 0 ) {
		close(fds[0]); // 关闭管道读
		sleep(2);
		write(fds[1], "abc", 3);
		close(fds[1]);
	} else {
		close(fds[1]);
		char buf[12] = {};
		read(fds[0], buf, 12);
		close(fds[0]);
		printf("parent : %s\n" ,buf);
	}
}
