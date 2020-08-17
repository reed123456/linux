#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define PRO 3
#define CUS 2

pthread_t tid[PRO+CUS];

pthread_mutex_t mutex;
pthread_cond_t cond;

int g_data = 0;

void *pro(void *arg) {
	int id = *(int*)arg;
	free(arg);
	while ( 1 ) {
		pthread_mutex_lock(&mutex);
		printf("生产者线程%d,开始生产产品, 编号:%d\n", id, g_data);
		g_data ++;
		sleep(rand() % 3);
		printf("生产者线程%d,生产出产品 编号:%d\n", id, g_data-1);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *cus(void *arg) {
	int id = *(int*)arg;
	free(arg);
	while ( 1 ) {
		pthread_mutex_lock(&mutex);

		while ( g_data <= 0 ) {
			printf("没有产品可以消费,%d消费者线程休息\n", id);
			pthread_cond_wait(&cond, &mutex);
			printf("%d消费者线程被唤醒\n", id);
		}
		printf("%d线程开始消费产品\n", id);
		g_data --;
		printf("%d线程消费产品结束\n", id);
		pthread_mutex_unlock(&mutex);
	}
}
int main( void ) {
	int i;

	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);

	for (i=0; i<PRO; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		pthread_create(&tid[i], NULL, pro, (void*)p);
	}

	for (i=0; i<CUS; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		pthread_create(&tid[PRO+i], NULL, cus, (void*)p);
	}

	for (i=0; i<PRO+CUS; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}

