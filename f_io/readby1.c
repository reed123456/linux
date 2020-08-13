#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void set_flg(int fd, int flag) {
	int flags = fcntl(fd, F_GETFL, 0);
	flags |= flag;
	fcntl(fd, F_SETFL, flags);
}

int main( void ) {
	char buf[1024] = {};
	write(1, "input > ", 8);
	set_flg(0, O_NONBLOCK);
	int ret = read(0, buf, 1024);
	if ( ret == 0 ) {
		printf("read EOF\n");
		return 0;
	}
	if ( ret == -1 ) {
		perror("read");
		return 0;
	}

	printf("buf=[%s]\n", buf);
}
