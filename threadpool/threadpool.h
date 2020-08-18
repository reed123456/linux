#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <pthread.h>

typedef struct node_ {
	void *(*func)(void*arg); // callback function
	void *arg; // argument of callback funciton
	struct node_ *next;
}node_t;

typedef struct threadpool_ {
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	node_t *first;
	node_t *last;
	int max_thread;
	int counter;
	int idle; // number of not working thread
	int quit; // if exit this threadpool quit=1, else quit=0
}threadpool_t;

void threadpool_init(threadpool_t *thread, int num);
void threadpool_add_task(threadpool_t *thread, void *(*func)(void *), void *args);

void threadpool_destroy(threadpool_t *thread);

#endif //__THREADPOOL_H__

