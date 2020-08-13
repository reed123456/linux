#ifndef __GLOBAL_H_ 
#define __GLOBAL_H_

struct operator{
	int (*pfunc)(int , int);
	char *name;
	char op;
}; 

extern char g_op;
extern int (*pFUNC)(int , int);
#endif 
