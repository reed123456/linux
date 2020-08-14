#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s){
	printf("你弄不死我\n");
}

int main( void) {
	signal(SIGINT, handler);

	for ( ; ; ) {
		printf(".");
		fflush(stdout);
		sleep(1);
	}
}
