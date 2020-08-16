#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

void P(int id) {
	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op = -1;
	sb[0].sem_flg = 0;
	semop(id, sb, 1);
}

void V(int id) {
	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op = 1;
	sb[0].sem_flg = 0;
	semop(id, sb, 1);
}

union semun {int val; };

void setval(int id, int val) {
	union semun su;
	su.val = val;
	semctl(id, 0, SETVAL, su);
}
int main( void ) {
	int shmid = shmget(1234, 0, 0);
	int sema = semget(1234, 0, 0);
	int semb = semget(1235, 0, 0);

	int *pi = shmat(shmid, NULL, 0);
	while ( 1 ) {
		P(semb);
		printf("recv : %d\n", *pi);
		V(sema);
	}
}

