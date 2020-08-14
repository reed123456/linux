#include <stdio.h>
#include <stdlib.h>

int main( void ) {
	int i, j;
	for (i=1; i<=9; i++) {
		for (j=1; j<=i; j++) {
			printf("\033[3%dm%dX%d=%-3d ", (i%8), j, i, i*j);
		}
		printf("\n");
	}
	printf("\033[0m");
}
