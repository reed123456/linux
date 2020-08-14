#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handler(int s) {
	printf("recv %d \n", s );
}

int main( void ) {
	signal(SIGALRM, handler);

	struct itimerval it;

	it.it_value.tv_sec = 5;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec= 0;

	setitimer(ITIMER_REAL, &it, NULL);

	for ( ; ; ) {
		printf(".");
		fflush(stdout);
		sleep(1);
	}	
}
