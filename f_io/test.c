#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 10

void main (void) {
	int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_WRONLY);
	if (fd == -1){
		perror("open");
		exit(1);
	}

	printf("open ok.");

	while (1){
		char buf[BUF_SIZE+1];
		memset(buf, 0x00, sizeof(buf));
		int r = read(fd, buf, BUF_SIZE);
		if (r <= 0){
			break;
		}
		write(fd2, buf, r);
		printf("%s", buf);
		fflush(stdout);
		sleep(1);
	}
	close(fd);
	close(fd2);
}
