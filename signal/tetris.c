#include <stdio.h>
#include <stdlib.h>

struct shape {
	int s[5][5];
};

#define FC 5
#define BC 7

struct shape shape_arr[7] = {
	{ 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,1,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,1,1,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,1,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,1,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,1,1,0,0, 0,1,1,0,0, 0,0,0,0,0, 0,0,0,0,0 },
	{ 0,0,0,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,0,0,0 }
};

void draw_element(int x, int y, int c) {
	x *= 2;
	x++;
	y++;
	printf("\033[%d;%dH\033[3%dm\033[4%dm[]\033[?25l\033[0m", y, x, c, c);
	fflush(stdout);
}
// 从x，y位置开始将p图形绘制成c颜色
void draw_shape(int x, int y, struct shape p, int c) {
	int i, j;
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++) {
			if ( p.s[i][j] != 0 ) {
				draw_element(x+j, y+i, c);
			}
		}
	}
}

int main( void ) {
	int i;
	for (i=0; i<10; i++) {
		draw_shape(10, i, shape_arr[0], FC);
		sleep(1);
		draw_shape(10, i, shape_arr[0], BC);
	}
	printf("\033[?25h");
}
