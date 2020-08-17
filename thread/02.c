#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *r1( void * argv ) {
	const char *str = (const char *)argv;

	int i;
	for (i=0; ; ) {
		i++;
		//printf("I'm %s\n", str);
		#if 0
		if ( i == 3 )
		pthread_exit(NULL); // 结束当前线程, 线程自杀
		#endif
	}
		
	return NULL;
}

int main( void ) {
	pthread_t tid;
	
	pthread_create(&tid, NULL, r1, "thread 1");
	
	sleep(3);
	pthread_cancel(tid); // 他杀，杀死tid线程，tid线程到能够被cancel的点才会取消。
	printf("cancel return\n");
	
	pthread_join(tid, NULL); // 阻塞，直到tid线程结束，回收僵尸线程
	printf("main exit\n");
}
