#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SP 32
#define row 21
#define col 12

int sel_block(void);
void move_block(int[row][col], int, int);
void print_block(int[row][col], int[row][col], int, int, int);
void backup_block(int[row][col], int[row][col]);
void gotoxy(int, int);
int key_control(char, int*, int*, int*, int[row][col]);
void set_line(int[row][col]);
void print_line(int[row][col], int, int);
void put_block(int[row][col], int, int, int, int);
int wall(int[row][col]);
int ground(int[row][col]);
int rotate(int[row][col], int, int, int, int);
void block_ground(int[row][col]);

char block[7][4][4][4] =
{ { { { 0, 0, 0, 0 },					//L 블록
	{ 0, 0, 0, 1},
	{ 0, 1, 1, 1 },
	{ 0, 0, 0, 0 } },
{	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 0, 1, 1, 1 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
{	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } } },

{ { { 0, 0, 0, 0 },					//역 L 블록
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 1 },
	{ 0, 0, 0, 0 } },
{	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } } },

{ { { 0, 0, 0, 0 },					// ㅁ 블록
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } } },

{ { { 0, 0, 1, 0 },					//일자 블록
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 } },
{	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 1 } },
{	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 1, 0 } },
{	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 1 } } },

{ { { 0, 0, 0, 0 },					// ㅗ 블록
	{ 0, 1, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } } },

{ { { 0, 0, 0, 0 },					//ㄱ_ 블록
	{ 1, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } } },

{ { { 0, 0, 0, 0 },					//역 ㄱ_ 블록
	{ 0, 1, 1, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 0, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 0, 0, 0 } },
{	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 1, 0 },
	{ 0, 0, 0, 0 } } }
};

int xb, yb;

typedef struct loc_arr {
	int loc_arr[row][col];
}Loc_arr;

int main() {
	system("mode con: cols=90 lines=35");
	int rand_num = sel_block();
	int rotation = 0;
	char cursor = NULL;
	int arr_row = 0, arr_col = col/2;
	int x = 0, y = 0;
	Loc_arr loc_arr;
	Loc_arr loc_arr_b;
	int move;

	set_line(loc_arr.loc_arr);
	print_line(loc_arr.loc_arr, x, y);
	put_block(loc_arr.loc_arr, rand_num, rotation, arr_row, arr_col);

	while (1) {
		move = -1;
		x = 0, y = 0;
		if (kbhit())
			move = key_control(cursor, &x, &y, &rotation, loc_arr.loc_arr);
		if (move == 1)
			move_block(loc_arr.loc_arr, x, y);
		if (move == 2)
			rotate(loc_arr.loc_arr, x, y, rand_num, rotation);
		print_block(loc_arr.loc_arr, loc_arr_b.loc_arr, move, x, y);
		backup_block(loc_arr.loc_arr, loc_arr_b.loc_arr);
		if (ground(loc_arr.loc_arr) == -1)
		{
			block_ground(loc_arr.loc_arr);
			rand_num = sel_block();
			put_block(loc_arr.loc_arr, rand_num, rotation, arr_row, arr_col);
		}
	}
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int key_control(char cursor, int *x, int *y, int *rotation, int loc_arr[row][col])
{
	cursor = getch();
	switch (cursor)
	{
	case UP:
		if (*rotation == 3)
			*rotation = 0;
		else
			(*rotation) += 1;
		return 2;

	case DOWN:
		if(ground(loc_arr) != -1)
			*y += 1;
		return 1;

	case LEFT:
		if (wall(loc_arr) != -1)
			*x -= 1;
		return 1;

	case RIGHT:
		if (wall(loc_arr) != 1)
			*x += 1;
		return 1;
	}
	return 0;
}

int sel_block(void)
{
	int random;

	srand(time(NULL));

	random = rand() % 7;

	return random;
}

void move_block(int loc_arr[row][col], int x, int y)
{
	int i, j;
	Loc_arr tmp = { 0 };

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (loc_arr[i][j] == 1)
			{
				tmp.loc_arr[i+y][j+x] = 1;
				loc_arr[i][j] = 0;
			}
		}
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (tmp.loc_arr[i][j] == 1)
					loc_arr[i][j] = 1;
		}
	}
}

void print_block(int loc_arr[row][col], int loc_arr_b[row][col], int move, int x, int y)
{
	int i, j;
	int ax = 6, ay = 2;
	
	for (i = 0; i < row; i++)
	{
		ax = 6;
		for (j = 0; j < col; j++)
		{
			if (loc_arr_b[i][j] != loc_arr[i][j])
			{
				gotoxy(ax + (j + 1) * 2, ay + i - 1);
				if (loc_arr[i][j] == 1)
					printf("■");
				else if (loc_arr[i][j] == 3)
					printf("▣");
				else if (loc_arr[i][j] == 0)
					printf("  ");
			}
		}
	}
}

void backup_block(int loc_arr[row][col], int loc_arr_b[row][col])
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			loc_arr_b[i][j] = loc_arr[i][j];
	}
}

void set_line(int loc_arr[row][col])
{
	int i, j;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (j == 0 || j == col - 1)
				loc_arr[i][j] = 4;
			else if (i == row - 1)
				loc_arr[i][j] = 5;
			else
				loc_arr[i][j] = 0;
		}
	}
}

void print_line(int loc_arr[row][col], int x, int y)
{
	int i, j;
	int ax = 8;
	int ay = 2;
	
	for (i = 0; i < row; i++)
	{
		gotoxy(ax, ay + i);
		for (j = 0; j < col; j++)
		{
			if (loc_arr[i][j] == 4)
				printf("▩");
			else if (loc_arr[i][j] == 5)
				printf("▩");
			else
				printf("  ");
		}
	}
}

void put_block(int loc_arr[row][col], int rand_num, int rotation, int arr_row, int arr_col)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[rand_num][rotation][i][j] == 1)
			loc_arr[arr_row + i][arr_col + j-2] = 1;
		}
	}
}

int wall(int loc_arr[row][col])
{
	int i;

	for (i = 0; i < row; i++)
	{
		if (loc_arr[i][1] == 1)					//왼쪽 벽
			return -1;
		else if (loc_arr[i][10] == 1)			//오른쪽 벽
			return 1;
	}
	return 0;
	
}

int ground(int loc_arr[row][col])
{
	int i;
	for (i = 0; i < col; i++)
	{
		if (loc_arr[20][i] == 1)
			return -1;
	}
	return 0;
}

int rotate(int loc_arr[row][col], int x, int y, int rand_num, int rotation)
{
	int i, j, k, l, xp = 0, yp = -1;
	Loc_arr rotate_back;

	if (ground(loc_arr) == -1)
	{
		if (rand_num == 3);
		else
			yp = -1;
	}

	if (wall(loc_arr) == 1)				//오른쪽 벽
	{
		if (rand_num == 3)
			xp = -2;
		else
			xp = -1;
	}	

	if (wall(loc_arr) == -1)			//왼쪽 벽
		xp = 1;
	
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (rand_num == 3 && (rotation == 0 || rotation == 2))
				yp = -3;
			if (rotate_back.loc_arr[i][9] == 1 && rand_num == 3 && (rotation == 1 || rotation == 3))
				xp = -1;
			if (loc_arr[i][j] == 1)
			{
				rotate_back.loc_arr[i][j] = 1;
				loc_arr[i][j] = 0;
			}
		}
	}

	for (i = 0; j < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (rotate_back.loc_arr[i][j] == 1)
			{
				for (k = 0; k < 4; k++)
				{
					for (l = 0; l < 4; l++)
					{
						
						if (block[rand_num][rotation][k][l] == 1)
							loc_arr[y + i + k + yp][x + j + l - 1 + xp] = 1;
					}
				}
				return 0;
			}
		}
	}
}

void block_ground(int loc_arr[row][col])
{
	int i, j;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (loc_arr[i][j] == 1)
				loc_arr[i][j] = 3;
		}
	}
}