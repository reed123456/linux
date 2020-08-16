#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main( void ) {
	int id = semget(1234, 0, 0);

	struct sembuf sb[1];

	sb[0].sem_num = 0;
	sb[0].sem_op = -1;
	sb[0].sem_flg = 0;

	semop(id, sb, 1);
}

