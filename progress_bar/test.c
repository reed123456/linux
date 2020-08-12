#include <stdio.h>
#include <unistd.h>

int main(void){
	char buf[101] = "";
	int i;
	char *info = "|/-\\";
	for (i = 0; i < 100; i++){
		buf[i] = '#';
		printf("\r[%-100s][%d%%]%c", buf, i, info[i%4]);
		fflush(stdout);
		usleep(200000);
	}
}
