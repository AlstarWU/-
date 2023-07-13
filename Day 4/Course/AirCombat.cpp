#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

#define PI 3.14

typedef struct {
	int x, y;
}Star;

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
	int r, alpha = 0;
	Star s0 = {0,1}, *s = &s0;
	
	
	srand((unsigned)time(NULL));
	
	do{
		gotoxy(0, 0);
		r=rand()%30;
		alpha=rand()%360;
		s->x =r*sin(alpha/180.0*PI)+40;
		s->y =r*cos(alpha/180.0*PI)+40;
		printf("The position of star is at (%d,%d)", s->x, s->y );
		gotoxy( s->x, s->y);
		printf("*");
		if (_kbhit())
			if ('C' == _getch() || 'c' == _getch()) system("Cls");
		Sleep(50);
	} while (1);
	return 0;
}
