#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s) {
	printf("recv %d\n", s);
	exit(0);
}

int main( void ) {
	signal(SIGUSR1, handler);

	pid_t pid = fork();
	if ( pid == 0 ) {
		sleep(3);
		kill(getppid(), SIGUSR1);

	} else {
		for ( ; ; ) {
			printf(".");
			fflush(stdout);
		}
	}
}

