#include <stdio.h>
#include <stdlib.h>

#include "threadpool.h"

void *myfun(void *args) {
	int num = *(int*)args;
	free(args);
	printf("%d task running on %p\n", num, pthread_self());
	sleep(1);
	return NULL;
}

int main( void ) {
	threadpool_t pool;

	threadpool_init(&pool, 3);
	int i;

	for (i=0; i<5; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		threadpool_add_task(&pool, myfun, (void*)p);
	}

	threadpool_destroy(&pool);
}

