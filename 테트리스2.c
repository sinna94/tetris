#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SP 32
#define row 21
#define col 12

int sel_block(void);													/*�������� ������ ����� �����ִ� �Լ�*/
void move_block(int[row][col], int, int);								/*����� �̵���Ű�� �Լ�*/
void print_block(int[row][col], int[row][col], int, int, int);			/*����� ������ִ� �Լ�*/
void backup_block(int[row][col], int[row][col]);						/*������ �ٸ� �͸� ����ϱ� ���� ����ϴ� �Լ�*/
void gotoxy(int, int);													/*��ǥ �̵� �Լ�*/
int key_control(char, int*, int*, int*, int[row][col]);					/*Ű�� �Է¹޾Ƽ� ���� ��ȯ�ϴ� �Լ�*/
void set_line(int[row][col]);											/*�׵θ��� �׸��� �Լ�*/
void print_line(int[row][col], int, int);								/*�׵θ��� ����ϴ� �Լ�*/
void put_block(int[row][col], int, int, int, int);						/*����� ������ �迭�� �ִ� �Լ�*/
int wall(int[row][col]);												/*���� �浹�� ���� ��ȯ�ϴ� �Լ�*/
int ground(int[row][col]);												/*�ٴڿ� ����� ������ ���� ��ȯ�ϴ� �Լ�*/
int rotate(int[row][col], int, int, int, int);							/*����� ȸ����Ű�� �Լ�*/
void block_ground(int[row][col]);										/*����� ���� ������� �ٲٴ� �Լ�*/
int s_block(int[row][col]);												/*��� ���� ���� ��Ͽ� ������ ���� ��ȯ�ϴ� �Լ�*/
int s_block_rl(int[row][col]);											/*��� ���� ���� ��Ͽ� ������ ���� ��ȯ�ϴ� �Լ�*/
int line_full(int[row][col]);											/*�� ���� �� ���� ���� ��ȯ�ϴ� �Լ�*/
int delete_line(int[row][col], int);									/*�� ���� �����ϴ� �Լ�*/
void down_block(int[row][col]);											/*����� ��ĭ�� �������� �ϴ� �Լ�*/
void SPbar(int[row][col]);												/*�����̽��ٸ� ������ �۵��ϴ� �Լ�*/
void gameplay_1();														/*ȥ���ϱ� ���*/
void print_menu();														/*�޴� ��� �Լ�*/
int select_menu();														/*�޴� ���� �Լ�*/
void cursor_control(char , int *, int *);								/*�޴� ��ǥ �Է� �Լ�*/

char block[7][4][4][4] =
{ { { { 0, 0, 0, 0 },					//L ���
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

{ { { 0, 0, 0, 0 },					//�� L ���
	{ 1, 0, 0, 0 },
	{ 1, 1, 1, 0 },
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

{ { { 0, 0, 0, 0 },					// �� ���
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

{ { { 0, 0, 1, 0 },					//���� ���
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

{ { { 0, 0, 0, 0 },					// �� ���
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

{ { { 0, 0, 0, 0 },					//��_ ���
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

{ { { 0, 0, 0, 0 },					//�� ��_ ���
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
	int menu;

	system("mode con: cols=90 lines=35");
	print_menu();
	menu = select_menu();
	switch (menu)
	{
	case 1:
		system("cls");
		gameplay_1();
		break;

	case 2:

		break;

	case 3:

		break;
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
		if(ground(loc_arr) != -1 && s_block(loc_arr) != 0)
			*y += 1;
		return 1;

	case LEFT:
		if (wall(loc_arr) != -1 && s_block_rl(loc_arr) != -1) 
			*x -= 1;
		return 1;

	case RIGHT:
		if (wall(loc_arr) != 1 && s_block_rl(loc_arr) != 1)
			*x += 1;
		return 1;
	case SP:
		SPbar(loc_arr);
		return 3;
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
					printf("��");
				else if (loc_arr[i][j] == 3)
					printf("��");
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
				printf("��");
			else if (loc_arr[i][j] == 5)
				printf("��");
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
		if (loc_arr[i][1] == 1)					//���� ��
			return -1;
		else if (loc_arr[i][10] == 1)			//������ ��
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
	int i, j, k, l, xp = 0, yp = 0, rv=0;
	Loc_arr rotate_back;

	if (ground(loc_arr) == -1)
	{
		if (rand_num == 3);
		else
			yp = -1;
	}

	if (wall(loc_arr) == 1)				//������ ��
	{
		if (rand_num == 3)
			xp = -2;
		else
			xp = -1;
	}	
	
	if (wall(loc_arr) == -1)			//���� ��
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

	for (i = 0; i < row; i++)
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
						{
							if (loc_arr[y + i + k + yp][x + j + l - 1 + xp] == 3)
							{
								rv = 1;
								break;
							}
								
							else
							{
								loc_arr[y + i + k + yp][x + j + l - 1 + xp] = 1;
							}
						}
							
					}
				}
				if (rv == 1)
					break;
				else
					return 0;
			}
		}
	}
	return 0;
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

int s_block(int loc_arr[row][col])
{
	int i, j;

	for (i = 0; i < row - 1; i++)
	{
		for (j = 1; j < col - 1; j++)
		{
			if (loc_arr[i][j] == 1)
			{
				if (loc_arr[i + 1][j] == 3)
					return 0;
			}
		}
	}
	return -2;
}

int s_block_rl(int loc_arr[row][col])
{
	int i, j;

	for (i = 0; i < row - 1; i++)
	{
		for (j = 1; j < col - 1; j++)
		{
			if (loc_arr[i][j] == 1)
			{
				if (loc_arr[i][j - 1] == 3)
					return -1;
				else if (loc_arr[i][j + 1] == 3)
					return 1;
			}
		}
	}
	return -2;
}

int line_full(int loc_arr[row][col])
{
	int i, j, full = 0, ck = 0;

	for (i = 0; i < row; i++)
	{
		ck = 0;
		for (j = 0; j < col; j++)
		{
			if (loc_arr[i][j] == 3)
				ck += 1;
		}
		if (ck == 10)
			full = i;
	}

	return full;
}

int delete_line(int loc_arr[row][col], int full)
{
	int i, j, r = -1, top=0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (loc_arr[i][j] == 1)
			{
				top = i;
				break;
			}
		}
	}

	for (i = full - 1; i > top; i--)
	{
		for (j = 1; j < col - 1; j++)
		{
			loc_arr[i + 1][j] = loc_arr[i][j];			
		}
		r = 1;
	}
	return r;
}

void down_block(int loc_arr[row][col])
{
	int i, j;
	for (i = row - 2; i >= 0; i--)
	{
		for (j = 1; j < col; j++)
		{
			if (loc_arr[i][j] == 1)
			{
				loc_arr[i + 1][j] = loc_arr[i][j];
				loc_arr[i][j] = 0;
			}
		}
	}
}

void SPbar(int loc_arr[row][col])
{
	while ((ground(loc_arr) != -1 && s_block(loc_arr) != 0))
	{
		down_block(loc_arr);
	}
}

void gameplay_1()
{
	int rand_num = sel_block();
	int rotation = 0;
	char cursor = NULL;
	int arr_row = 0, arr_col = col / 2;
	int x = 0, y = 0;
	int move, full = 0;
	int del = 0;
	int time = 0, lev = 20000;

	Loc_arr loc_arr;
	Loc_arr loc_arr_b;

	set_line(loc_arr.loc_arr);
	print_line(loc_arr.loc_arr, x, y);
	put_block(loc_arr.loc_arr, rand_num, rotation, arr_row, arr_col);

	while (1) {
		move = -1;
		x = 0, y = 0;
		full = 0, del = 0;
		if (kbhit())
			move = key_control(cursor, &x, &y, &rotation, loc_arr.loc_arr);
		if (move == 1)
			move_block(loc_arr.loc_arr, x, y);
		if (move == 2)
			rotate(loc_arr.loc_arr, x, y, rand_num, rotation);
		print_block(loc_arr.loc_arr, loc_arr_b.loc_arr, move, x, y);
		backup_block(loc_arr.loc_arr, loc_arr_b.loc_arr);

		full = line_full(loc_arr.loc_arr);
		if (full)
		{
			del = delete_line(loc_arr.loc_arr, full);
			lev -= 50;
		}

		if (((ground(loc_arr.loc_arr) == -1 || s_block(loc_arr.loc_arr) == 0) && time % 10000 == 0) || move == 3)
		{
			block_ground(loc_arr.loc_arr);
			rand_num = sel_block();
			if (del != -1)
			{
				rotation = 0;
				put_block(loc_arr.loc_arr, rand_num, rotation, arr_row, arr_col);
			}
		}
		if (time % lev == 0)
			down_block(loc_arr.loc_arr);
		time += 2;
	}
}

void print_menu()
{
	gotoxy(35, 10);
	printf("��Ʈ����");
	gotoxy(35, 12);
	printf("1. 1�� �÷���");
	gotoxy(35, 14);
	printf("2. 2�� �÷���");
	gotoxy(35, 16);
	printf("3. ��� Ȯ��");
	gotoxy(35, 18);
	printf("4. ����");
}

int select_menu()
{
	int x = 33, y = 12, space = 0;					/*x, y�� �޴��� ��µ� ��ǥ*/
	char cursor;

	gotoxy(x, y);
	printf("��");

	while (1)
	{
		cursor = getch();							/*Ű���忡�� �Է� ����*/
		gotoxy(x, y);
		printf(" ");
		cursor_control(cursor, &y, &space);		/*Ű���忡�� �Է� ���� cursor ������ y, space �� ����*/

		if ((y > 18))								/*y���� �ִ� �� ����*/
			y -= 2;

		else if (y < 12)							/*y���� �ּ� �� ����*/
			y += 2;

		gotoxy(x, y);
		printf("��");

		if (space == 1)								/*���ý� �ݺ��� Ż��*/
			break;
	}

	switch (y) {									/*y ���� ���� ����*/
	case 12:
		return 1;

	case 14:
		return 2;

	case 16:
		return 3;

	case 18:
		exit(1);

	default:
		break;
	}
}

void cursor_control(char cursor, int *y, int *space)
{
	switch (cursor)
	{
	case UP:				/*����Ű ��*/
		*y -= 2;
		break;

	case DOWN:
		*y += 2;			/*����Ű �Ʒ�*/
		break;

	case SP:				/*�����̽� ��*/
		*space = 1;
		break;

	default:
		break;
	}
}