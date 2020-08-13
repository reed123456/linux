#include <stdlib.h>

#include "global.h"
#include "add.h"
#include "sub.h"
#include "mul.h"
#include "power.h"

int (*pFUNC)(int , int);
char g_op;
struct operator ops[] = {
	{add, "add", '+'},
	{sub, "sub", '-'},
	{mul, "mul", '*'},
	{power, "pow", '^'},
	{NULL, NULL}

};
