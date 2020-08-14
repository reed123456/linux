#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s) {
	printf("recv %d\n", s);
}
int main( void ) {
	signal(SIGINT, handler);

	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);
	int i;
	for (i=0; i<5; i++) {
		printf("开始拷贝%d集视频\n", i+1);
		sleep(3);
		printf("第%d集视频拷贝完毕\n", i+1);
	}

	// 解除信号屏蔽
	sigprocmask(SIG_UNBLOCK, &set, NULL);

	for ( ; ; ) {
		printf(".");
		sleep(1);
		fflush(stdout);
	}
}
