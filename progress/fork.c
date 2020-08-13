#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	printf("before fork()\n");
	pid_t pid = fork();
	if (pid == 0){
		printf("child process :  getpid = %d, return value = %d.\n", getpid(), pid); 
	}else{
		printf("parents process :  getpid = %d, return value = %d.\n", getpid(), pid); 
	}	
	getchar();
}
