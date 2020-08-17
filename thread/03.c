#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main( void ) {
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	pid_t pid = fork();

	if ( pid == 0 ) {
		exit(0);
	}

	for ( ; ; )
	 // pause();
	 printf(".");
	 fflush(stdout);
}

