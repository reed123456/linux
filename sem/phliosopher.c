#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semid;

union semun {
	int val;
};
/*
void zhexuejia(int no) {
	while ( 1 ) {
		printf("%d哲学家在思考问题\n", no);
		//sleep(rand()%5);
		printf("%d哲学家饿了\n", no);
		
		struct sembuf sb[1];
		sb[0].sem_num = no;
		sb[0].sem_op = -1;
		sb[0].sem_flg = 0;
		semop(semid, sb, 1); // P左手
		
		sb[0].sem_num = (no+1)%5;
		semop(semid, sb, 1); // P右手
		
		printf("%d哲学家开始吃饭\n", no);
		//sleep(rand()%5);
		printf("%d哲学家吃完饭\n", no);
		
		
		sb[0].sem_num = no;
		sb[0].sem_op = 1;
		sb[0].sem_flg = 0;
		semop(semid, sb, 1);
		
		sb[0].sem_num = (no+1)%5;
		semop(semid, sb, 1);
	}
}
*/
void zhexuejia(int no) {
	while ( 1 ) {
		printf("%d哲学家在思考问题\n", no);
		sleep(rand()%5);
		printf("%d哲学家饿了\n", no);
		
		struct sembuf sb[2] = {{no, -1, 0}, {(no+1)%5, -1, 0}};
		semop(semid, sb, 2);
		
		printf("%d哲学家开始吃饭\n", no);
		//sleep(rand()%5);
		printf("%d哲学家吃完饭\n", no);
		
		struct sembuf sb2[2] = {{no, 1, 0}, {(no+1)%5, 1, 0}};
		semop(semid, sb2, 2);
	}
}
		
int main( void ) {
	semid = semget(1234, 5, IPC_CREAT|0644);

	srand(getpid());
	int i;
	union semun su;
	su.val = 1;
	for (i=0; i<5; i++) {
		semctl(semid, i, SETVAL, su);
	}

	int no = 0;
	for (i=1; i<5; i++) {
		pid_t pid = fork();
		if ( pid == 0 ) {
			no = i;
			break;
		}
	}

	zhexuejia(no);
}
