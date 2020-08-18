#include <stdio.h>
#include <stdlib.h>
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

void *thread_routine(void *arg) {
	threadpool_t *pool = (threadpool_t*)arg;
	printf("%p thread create\n", pthread_self());
	while ( 1 ) {
		pthread_mutex_lock(&pool->mutex);
		pool->idle++;

		while ( pool->first == NULL && pool->quit != 1 ) {
			printf("%p thread wait for task\n", pthread_self());
			pthread_cond_wait(&pool->cond, &pool->mutex);
		}
		pool->idle--;

		if ( pool->first != NULL ) {
			node_t *tmp = pool->first;
			pool->first = tmp->next;

			pthread_mutex_unlock(&pool->mutex);
			tmp->func(tmp->arg);
			free(tmp);
			pthread_mutex_lock(&pool->mutex);
		}
		if ( pool->quit == 1 && pool->first == NULL ) {
			pool->counter--;
			if ( pool->counter == 0 )
			  pthread_cond_signal(&pool->cond);
			pthread_mutex_unlock(&pool->mutex);
			break;
		}

		pthread_mutex_unlock(&pool->mutex);
	}

	printf("%p thread exit\n", pthread_self());
}


void threadpool_add_task(threadpool_t *thread, void *(*func)(void *), void *args) {
	node_t *newtask = (node_t*)malloc(sizeof(node_t));
	newtask->func = func;
	newtask->arg = args;
	newtask->next = NULL;

	pthread_mutex_lock(&thread->mutex);
	if ( thread->first == NULL ) {
		thread->first = newtask;
	} else {
		thread->last->next = newtask;
	}
	thread->last = newtask;

	if ( thread->idle > 0 ) {
		pthread_cond_signal(&thread->cond);
	} else if ( thread->counter < thread->max_thread ) {
		pthread_t tid;
		pthread_create(&tid, NULL, thread_routine, thread);
		thread->counter++;
	}

	pthread_mutex_unlock(&thread->mutex);
}
void threadpool_destroy(threadpool_t *thread) {
	printf("destroy thread pool\n");
	if ( thread->quit == 1 )
	  return;

	pthread_mutex_lock(&thread->mutex);
	thread->quit = 1;

	if ( thread->counter > 0 ) {
		if ( thread->idle > 0 )
		  pthread_cond_broadcast(&thread->cond);
		while ( thread->counter > 0 )
		  pthread_cond_wait(&thread->cond, &thread->mutex);
	}

	pthread_mutex_unlock(&thread->mutex);
}

