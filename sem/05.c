#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *rout(void* arg) {
	while ( 1 ) {
		printf("我是线程1\n");
	}
}

int main( void ) {
	pthread_t tid;

	pthread_create(&tid, NULL, rout, NULL);

	while ( 1 ) {
		printf("我是main线程\n");
	}
}
