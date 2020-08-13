#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main( void ) {
	int fd = open("test.txt", O_RDWR);
	struct flock lock;

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	if ( fcntl(fd, F_SETLKW, &lock) == 0 ) {
		printf("lock ok\n");
	} else {
		perror("lock err\n");
		exit(0);
	}	

	printf("enter any key to unlock\n");
	getchar();
	lock.l_type = F_UNLCK;
	if ( fcntl(fd, F_SETLKW, &lock) == 0 ) {
		printf(" unlock ok\n");
	} else {
		perror("unlock");
		exit(0);
	}

	for ( ; ; ) {
		printf(".");
		fflush(stdout);
		sleep(1);
	}

	close(fd);
}
