#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void do_action(int argc, char *argv[]){
	pid_t pid = fork();
	if (pid == 0){
		//子进程，用argv[0]程序替换
		execvp(argv[0], argv);
	}else{
		//父进程wait子进程
		wait(NULL);
	}
}

void do_parse(char *buf){
	int argc = 0;
	char *argv[8] = {};
	int i;
	int flag = 0;

	for (i = 0; buf[i] != 0; i++){
		if (flag == 0 && !isspace(buf[i])){
			argv[argc++] = buf + i;
			flag = 1;
		}else if (flag == 1 && isspace(buf[i])){
			buf[i] = 0;
			flag = 0;
		}
	}

	argv[argc] = NULL;

	do_action(argc, argv);	
}

int main(void){
	char buf[1024];
	while(1){
		printf("[my shell]# ");
		memset(buf, 0x00, sizeof(buf));
		scanf("%[^\n]%*c", buf);
		do_parse(buf);
	}
}
