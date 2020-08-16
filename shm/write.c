#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main( void ) {
	int id = shmget(1234, 0, 0);

	int *pi = (int*)shmat(id, NULL, 0);

	printf("num:");
	scanf("%d", pi);

	getchar();
	getchar();
}
