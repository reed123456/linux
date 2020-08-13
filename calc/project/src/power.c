#include "power.h"

int power(int a, int b){
	int ret = 1;
	int i;

	for (i = 0; i < b; ++i){
		ret *= a;
	}

	return ret;
}
