#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *r1(void*arg) {
	while ( 1 ) {
		sem_wait(&sem);//信号量-1，信号量为0阻塞，相当于P操作;
		printf("wait return\n");
	}
}

void *r2(void*arg) {
	while ( 1 ) {
		sleep(2);
		sem_post(&sem);//信号量+1，相当于V操作;
	}
}

int main( void ) {
	pthread_t t1, t2;
	sem_init(&sem, 0, 5);

	pthread_create(&t1, NULL, r1, NULL);
	pthread_create(&t2, NULL, r2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	sem_destroy(&sem);
}

