#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int ticket = 100;

pthread_mutex_t mutex;

void *r1( void *arg ) {
	const char *name = (const char *)arg;
	while ( 1 ) {
		pthread_mutex_lock(&mutex);
		if ( ticket > 0 ) {
			printf("%s 卖 %d\n", name, ticket);
			ticket --;
		} else {
			pthread_mutex_unlock(&mutex); // 别忘了，离开前要解锁
			break;
		}
		pthread_mutex_unlock(&mutex);
		usleep(100000);
	}
}
int main( void ) {
	pthread_t t1, t2, t3, t4;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, r1, "thread 1");
	pthread_create(&t2, NULL, r1, "thread 2");
	pthread_create(&t3, NULL, r1, "thread 3");
	pthread_create(&t4, NULL, r1, "thread 4");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	pthread_mutex_destroy(&mutex);
}

