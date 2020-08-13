#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "add.h"
#include "sub.h"
#include "mul.h"
#include "power.h"
#include "global.h"

extern struct operator ops[];
void do_math(int argc, char *argv[]){
	int i; 
	
	pFUNC = NULL;
	for (i = 0; ops[i].pfunc != NULL; i++){
		if (strcmp(argv[0], ops[i].name) == 0){
			pFUNC = ops[i].pfunc;
			g_op = ops[i].op;
		break;
		}
	}
	
	if (pFUNC != NULL){
		int ret = pFUNC(atoi(argv[1]), atoi(argv[2]));
		printf("%s%c%s=%d\n", argv[1], g_op,  argv[2], ret);
	}else{
		printf("%s: Commomd not found.\n", argv[0]);
	}
	
}

void prase(char *buf){
	#define IN 1
	#define OUT 0
	int flag = OUT;
	int argc = 0;
	char *argv[20];
	
	int i;
	for (i = 0; buf[i] != '\0';++i){
		if (flag == OUT && !isspace(buf[i])){
			argv[argc++] = buf + i;
			flag = IN;
		}
		else if (isspace(buf[i])){
			flag = OUT;
			buf[i] = '\0';
		}
	}
	argv[argc] = NULL;
	do_math(argc, argv);	
}

int main(void){
	char buf[1024];

	while(1){
		printf(">");
		memset(buf, 0x00, sizeof(buf));
		scanf("%[^\n]%*c", buf);
		prase(buf);
	}
}
