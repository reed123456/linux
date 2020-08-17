#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void call_back(void *arg) {
	printf("call_back()\n");
	//sleep(3);
	pthread_mutex_unlock(&mutex);
}
	
void *odd(void *arg) {
	int i;
	
	for (i=1; ; i+=2) {
		pthread_mutex_lock(&mutex);
		printf("odd() : %d\n", i);
		pthread_mutex_unlock(&mutex);
	}
}
void *even(void *arg) {
	int i;

	for (i=0; ; i+=2) {
		pthread_cleanup_push(call_back, NULL);
		pthread_mutex_lock(&mutex);
		printf("even() : %d\n", i);
		pthread_mutex_unlock(&mutex);
		pthread_cleanup_pop(1);
	}
}
int main( void ) {
	pthread_t t1, t2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, odd, NULL);
	pthread_create(&t2, NULL, even, NULL);

	sleep(3);
	pthread_cancel(t2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
}

