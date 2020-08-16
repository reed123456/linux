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
	int shmid = shmget(1234, sizeof(int), IPC_CREAT|0644);
	int sema = semget(1234, 1, IPC_CREAT|0644);
	int semb = semget(1235, 1, IPC_CREAT|0644);

	setval(sema, 1);
	setval(semb, 0);

	int num = 0;
	int *pi = shmat(shmid, NULL, 0);
	while ( 1 ) {
		P(sema);
		printf("开始装入数据,编号为%d\n", num);
		*pi = num++;
		sleep(1);
		printf("装入数据%d完成\n", num-1);
		V(semb);
	}
}
