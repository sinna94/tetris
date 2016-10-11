#include <stdio.h>
#include <windows.h>
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SP 32

int sel_block(void);
void print_block(int, int, int, int);
void gotoxy(int, int);
void key_control(char, int*, int*, int*);

char block[][4][4][4] =
{ {{{0, 0, 0, 0},					//L 블록
	{0, 0, 0, 1},
	{0, 1, 1, 1},
	{0, 0, 0, 0}},
   {{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 0, 0}},
   {{0, 0, 0, 0},
	{0, 1, 1, 1},
	{0, 1, 0, 0},
	{0, 0, 0, 0}},
   {{0, 0, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0}}},

	{ { { 0, 0, 0, 0 },					//역 L 블록
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 0, 0 } },
	  { { 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 } },
	  { { 0, 0, 0, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 0, 1 },
		{ 0, 0, 0, 0 } },
	  { { 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 } } },

		{ { { 0, 0, 0, 0 },					// ㅁ 블록
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } } },

		{ { { 0, 1, 0, 0 },					//일자 블록
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 } } },

		{ { { 0, 0, 0, 0 },					// ㅗ 블록
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 0, 0 } },
		{ { 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 0, 1, 1, 1 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 } } },

		{ { { 0, 0, 0, 0 },					//ㄱ_ 블록
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 } } },

		{ { { 0, 0, 0, 0 },					//역 ㄱ_ 블록
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 } },
		{ { 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 } } },
};
char block_b[][4] = { 0 };
int xb, yb;

int main() {
	int rand_num = sel_block();
	int rotaion = 0;
	char cursor;
	int x = 10, y = 10;
	while (1) {
		cursor = getch();
		key_control(cursor, &x, &y, &rotaion);
		print_block(rand_num, rotaion, x, y);
	}
}

void gotoxy(int x, int y)												
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void key_control(char cursor, int *x, int *y, int *rotation)
{
	switch (cursor)
	{
	case UP:
		if (*rotation == 3)
			*rotation = 0;
		else
			(*rotation) += 1;
		break;

	case DOWN:
		*y += 1;
		break;
	
	case LEFT:
		if(x != 0)
			*x -= 2;
		break;

	case RIGHT:
		*x += 2;
		break;
	}
}

int sel_block(void)
{
	int random;

	srand(time(NULL));
	
	random = rand() % 7;
	
	return random;
}

void print_block(int rand_num, int rotation, int x, int y)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(xb + j * 2, yb + i);
			if (block_b[i][j] == 1)
				printf("  ");
		}
		puts("");
	}

	xb = x, yb = y;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(x + j*2, y + i);
			
			if (block[rand_num][rotation][i][j] == 1)
			{
				block_b[i][j] = 1;
				printf("■");
			}
		}
		puts("");
	}
}