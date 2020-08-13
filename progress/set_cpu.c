#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main(void){
	cpu_set_t cpu;

	pid_t pid = fork();
	if(pid == 0){
		CPU_ZERO(&cpu);//把cpu变量清空
		CPU_SET(0, &cpu);//把变量cpu放到0号cpu上
		sched_setaffinity(0, sizeof(cpu_set_t), &cpu);
		while (1){
		}
	}else{
		CPU_ZERO(&cpu);
		CPU_SET(1, &cpu);
		sched_setaffinity(0, sizeof(cpu_set_t), &cpu);
		while (1){
		}
	}
}
