#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
	int val;
};

int main( void ) {
	int id = semget(1234, 0, 0);

	union semun su;
	su.val = 5;
	semctl(id, 0, SETVAL, su);
}

