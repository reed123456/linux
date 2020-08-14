#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s) {
	wait(NULL);
}

int main( void ) {
	int i;
	signal(SIGCHLD, handler);

	pid_t pid = fork();
	if ( pid == 0 ) {
		for (i=0; i<5; i++) {
			printf(".");
			sleep(1);
			fflush(stdout);
		}
	} else {
		for ( ; ; ) {
			printf("$");
			sleep(1);
			fflush(stdout);
		}
	}
}

