#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf buf;
void func(int s){
	printf("func(int s)\n");
	if (s == 1){
		longjmp(buf, 1);
	}else{
		longjmp(buf, 2);
	}

	printf("fun finsh\n");
}
int main(void){
	int r;
	printf("int main(void)\n");
	
	if ((r = setjmp(buf)) == 0){
		func(1);
	}else if (r == 1){
		printf("exception 1\n");
	}

	printf("main finish\n");
}
