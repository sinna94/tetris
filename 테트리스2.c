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
#define W 119
#define S 115
#define A 97
#define D 100
#define V 118

// ************ ���� ���� �Լ� ******************
void set_line(int[row][col]);											/*�׵θ��� �׸��� �Լ�*/

// ************ ��� ���� �Լ� ******************
int sel_block(void);													/*�������� ������ ����� �����ִ� �Լ�*/
void move_block(int[row][col], int, int);								/*����� �̵���Ű�� �Լ�*/
void print_block(int[row][col], int[row][col], int, int, int);			/*����� ������ִ� �Լ�*/
void backup_block(int[row][col], int[row][col]);						/*������ �ٸ� �͸� ����ϱ� ���� ����ϴ� �Լ�*/
int put_block(int[row][col], int, int, int, int);						/*����� ������ �迭�� �ִ� �Լ�*/
void down_block(int[row][col]);											/*����� ��ĭ�� �������� �ϴ� �Լ�*/
void shadow(int[row][col]);												/*�׸��� ���*/
int rotate(int[row][col], int, int, int, int);							/*����� ȸ����Ű�� �Լ�*/
void block_ground(int[row][col]);										/*����� ���� ������� �ٲٴ� �Լ�*/

// ************ ��� �浹 ���� �Լ� ******************
int ground(int[row][col]);												/*�ٴڿ� ����� ������ ���� ��ȯ�ϴ� �Լ�*/
int s_block(int[row][col]);												/*��� ���� ���� ��Ͽ� ������ ���� ��ȯ�ϴ� �Լ�*/
int s_block_rl(int[row][col]);											/*��� ���� ���� ��Ͽ� ������ ���� ��ȯ�ϴ� �Լ�*/
int wall(int[row][col]);												/*���� �浹�� ���� ��ȯ�ϴ� �Լ�*/

// ************ �޴� �Լ� ******************
void print_menu();														/*�޴� ��� �Լ�*/
int select_menu();														/*�޴� ���� �Լ�*/
void cursor_control(char, int *, int *);								/*�޴� ��ǥ �Է� �Լ�*/

// ************ ��� �Լ� ******************
void print_line(int[row][col], int, int);								/*�׵θ��� ����ϴ� �Լ�*/
void next_block_line_print(int, int);									/*������ ���� ��� ĭ �׸��� �Լ�*/
void next_block_print(int, int, int);									/*������ ���� ��� ��� �Լ�*/

// ************ Ű �Է� �Լ� ******************
int key_control(char, int*, int*, int*, int[row][col]);					/*Ű�� �Է¹޾Ƽ� ���� ��ȯ�ϴ� �Լ�*/
int key_control2(char, int*, int*, int*, int[row][col]);				/*Ű�� �Է¹޾Ƽ� ���� ��ȯ�ϴ� �Լ�, 2�ο�*/
void SPbar(int[row][col]);												/*�����̽��ٸ� ������ �۵��ϴ� �Լ�*/

// ************ ���� ��� �Լ� ******************
int line_full(int[row][col]);											/*�� ���� �� ���� ���� ��ȯ�ϴ� �Լ�*/
int search_top(int[row][col], int);										/*���� ���� ��� �� ���� ���� ��ġ�� ã�� �Լ�*/
int delete_line(int[row][col], int, int);	   	   	   	   	   	   	   	/*�� ���� �����ϴ� �Լ�*/
void save_line(int[row][col], int[], int);								/*�����Ǵ� �� �����ϴ� �Լ�*/
void toss_line(int[row][col], int[], int);								/*�����Ǵ� ���� ������� ������ �Լ�*/
void gameplay_1();														/*ȥ���ϱ� ���*/
void gameplay_2();														/*2�� ���*/

// ************ ���� �Լ� ******************
void save_score(double);												/*���� ����, ���� �Լ�*/
void print_score();														/*���� ��� �Լ�*/

void gotoxy(int, int);													/*��ǥ �̵� �Լ�*/

char block[7][4][4][4] =
{ { { { 0, 0, 0, 0 },					//L ���
{ 0, 0, 0, 1 },
{ 0, 1, 1, 1 },
{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },
{ 0, 1, 1, 1 },
{ 0, 1, 0, 0 },
{ 0, 0, 0, 0 } },
{ { 1, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 0, 0, 0 } } },

{ { { 0, 0, 0, 0 },					//�� L ���
{ 1, 0, 0, 0 },
{ 1, 1, 1, 0 },
{ 0, 0, 0, 0 } },
{ { 0, 1, 1, 0 },
{ 0, 1, 0, 0 },
{ 0, 1, 0, 0 },
{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },
{ 1, 1, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 0, 0 } } },

{ { { 0, 0, 0, 0 },					// �� ���
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

{ { { 0, 0, 1, 0 },					//���� ���
{ 0, 0, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 1, 0 } },
{ { 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 1, 1, 1, 1 } },
{ { 0, 0, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 1, 0 } },
{ { 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 0, 0, 0, 0 },
{ 1, 1, 1, 1 } } },

{ { { 0, 0, 0, 0 },					// �� ���
{ 0, 1, 0, 0 },
{ 1, 1, 1, 0 },
{ 0, 0, 0, 0 } },
{ { 0, 1, 0, 0 },
{ 0, 1, 1, 0 },
{ 0, 1, 0, 0 },
{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 },
{ 1, 1, 1, 0 },
{ 0, 1, 0, 0 },
{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },
{ 0, 1, 1, 0 },
{ 0, 0, 1, 0 },
{ 0, 0, 0, 0 } } },

{ { { 0, 0, 0, 0 },					//��_ ���
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

{ { { 0, 0, 0, 0 },					//�� ��_ ���
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
{ 0, 0, 0, 0 } } }
};

int xb, yb;

typedef struct loc_arr {												/*��Ʈ���� �������� ���� ����ü*/
	int loc_arr[row][col];
}Loc_arr;

typedef struct save {													/*���� �����ϱ� ���� ����ü*/
	char name[10];
	double score;
}save;

int main() {
	int menu;
	system("mode con: cols=90 lines=28");

	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	while (1)
	{
		system("cls");
		print_menu();
		menu = select_menu();
		switch (menu)
		{
		case 1:
			system("cls");
			gameplay_1();
			break;

		case 2:
			system("cls");
			gameplay_2();
			break;

		case 3:
			print_score();
			break;
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
	switch (cursor)
	{
	case UP:
		if (*rotation == 3)
			*rotation = 0;
		else
			(*rotation) += 1;
		return 2;

	case DOWN:
		if (ground(loc_arr) != -1 && s_block(loc_arr) != 0)
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
				tmp.loc_arr[i + y][j + x] = 1;
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

void print_block(int loc_arr[row][col], int loc_arr_b[row][col], int move, int ax, int ay)
{
	int i, j;
	int a;
	a = ax;
	for (i = 0; i < row; i++)
	{
		ax = a;
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
				else if (loc_arr[i][j] == 6)
					printf("��");
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

void print_line(int loc_arr[row][col], int ax, int ay)
{
	int i, j;

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

int put_block(int loc_arr[row][col], int rand_num, int rotation, int arr_row, int arr_col)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (block[rand_num][rotation][i][j] == 1)
			{
				if (loc_arr[arr_row + i][arr_col + j - 2] == 3)
					return -1;

				else
					loc_arr[arr_row + i][arr_col + j - 2] = 1;
			}
		}
	}
	return 0;
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
	int i, j, k, l, xp = 0, yp = 0, rv = 0;
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

int search_top(int loc_arr[row][col], int full)
{
	int i, j, top = 0;

	for (i = 0; i < row; i++)						/* ���� ��� �� ���� ���� ����� ���̸� ã�� top�� �����ϴ� �ݺ���*/
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

	return top;
}

int delete_line(int loc_arr[row][col], int full, int top)
{
	int i, j;

	for (i = full - 1; i > top; i--)				/*���� �� ���� ���� top���� ���پ� ������ �ݺ���*/
	{
		for (j = 1; j < col - 1; j++)
		{
			loc_arr[i + 1][j] = loc_arr[i][j];
		}
	}
	return 1;
}

void save_line(int loc_arr[row][col], int toss[], int full)
{
	int i;

	for (i = 1; i < col -1; i++)
	{
		toss[i - 1] = loc_arr[full][i];
	}
}

void toss_line(int loc_arr[row][col], int toss[], int top)
{
	int i, j, rand_num;

	for (i = top - 1; i < row - 1; i++)				/*top���� �� �Ʒ� ���� ���پ� �ø��� �ݺ���*/
	{
		for (j = 1; j < col - 1; j++)
		{
			loc_arr[i][j] = loc_arr[i + 1][j];
		}
	}

	srand(time(NULL));
	rand_num = rand() % 10;

	toss[rand_num] = 0;

	for (i = 1; i < col - 1; i++)
		loc_arr[row - 1][i] = toss[i - 1];
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
		down_block(loc_arr);
}

void gameplay_1()
{
	int rand_num = sel_block();
	int rotation = 0;
	char cursor = NULL;
	int arr_row = 0, arr_col = col / 2;
	int x = 0, y = 0;
	int move, full = 0;
	int time = 0, lev = 20000;
	double duration;
	int hour, min;
	double sec;
	int end = 0;
	int line_cnt = 40;
	int next_block;
	int top;

	// 2��°�� ���� ���
	next_block = rand() % 7;

	clock_t start, finish;

	Loc_arr loc_arr;
	Loc_arr loc_arr_b;

	// ���� ����, ��� ���
	set_line(loc_arr.loc_arr);
	print_line(loc_arr.loc_arr, 8, 2);
	next_block_line_print(40, 4);
	put_block(loc_arr.loc_arr, rand_num, rotation, arr_row, arr_col);
	next_block_print(42, 6, next_block);

	// ���� ���� 
	start = clock();
	while (1) {
		gotoxy(42, 15);
		printf("���� ��: %0d", line_cnt);
		move = -1;
		x = 0, y = 0;
		full = 0;

		// Ű �Է� ��
		if (kbhit())
		{
			cursor = getch();
			move = key_control(cursor, &x, &y, &rotation, loc_arr.loc_arr);
		}

		// ��� �̵�
		if (move == 1)
			move_block(loc_arr.loc_arr, x, y);
		
		// ��� ȸ��
		if (move == 2)
			rotate(loc_arr.loc_arr, x, y, rand_num, rotation);
		
		// ��� ���, ���
		print_block(loc_arr.loc_arr, loc_arr_b.loc_arr, move, 6, 2);
		backup_block(loc_arr.loc_arr, loc_arr_b.loc_arr);

		// ������ �� á���� Ȯ��
		full = line_full(loc_arr.loc_arr);

		// ������ �� �� ���
		if (full)
		{
			top = search_top(loc_arr.loc_arr, full);
			delete_line(loc_arr.loc_arr, full, top);
			line_cnt--;
			if (line_cnt == 0)
			{
				end = 1;
				break;
			}
			lev -= 50;
		}

		// ����� �ٴ�, ������Ͽ� ����� ���
		if (((ground(loc_arr.loc_arr) == -1 || s_block(loc_arr.loc_arr) == 0) && time % 10000 == 0) || move == 3)
		{
			block_ground(loc_arr.loc_arr);
			rotation = 0;
			rand_num = next_block;
			end = put_block(loc_arr.loc_arr, rand_num, rotation, arr_row, arr_col);
			if (end == -1)
				break;
			next_block = sel_block();
			next_block_print(42, 6, next_block);
		}

		// �׸���
		shadow(loc_arr.loc_arr);

		// �ð��� ���� ����� ������
		if (time % lev == 0)
			down_block(loc_arr.loc_arr);

		time += 2;

		// ���� ���� ���� ���� �ð� ���
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		min = duration / 60;
		sec = duration;
		if (sec > 60)
			sec -= min * 60;
		gotoxy(42, 3);
		printf("%d:%.2lf", min, sec);
	}

	system("cls");

	// ���� ����
	if (end == -1)
	{
		gotoxy(43, 15);
		printf("����");
		Sleep(3000);
	}

	// ���� ����
	else if (end == 1)
	{
		gotoxy(43, 14);
		printf("����!");
		gotoxy(43, 15);
		printf("���� �ð�: %d:%.2lf", min, sec);
		save_score(duration);
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

void next_block_line_print(int x, int y)
{
	gotoxy(x, y++);
	printf("    NEXT");
	gotoxy(x, y++);
	printf("������������");
	gotoxy(x, y++);
	printf("��        ��");
	gotoxy(x, y++);
	printf("��        ��");
	gotoxy(x, y++);
	printf("��        ��");
	gotoxy(x, y++);
	printf("��        ��");
	gotoxy(x, y);
	printf("������������");
}

void next_block_print(int x, int y, int rand_num)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		gotoxy(x, y++);
		for (j = 0; j < 4; j++)
		{
			if (block[rand_num][0][i][j] == 1)
				printf("��");
			else
				printf("  ");
		}
	}
}

void save_score(double score)									/*���� ���� �Լ�*/
{

	FILE* fp;
	save file[11] = { NULL };								/*���� ������ ���� ����ü �迭*/
	save save;

	int i, j, k = 0;

	if ((fp = fopen("score.txt", "r")) == NULL);				/*�б� ���� score.txt ����*/

	else {													/*������ �ִٸ�*/
		if (fp != NULL)
		{
			for (k = 0; k < 10; k++)						/*score.txt�� �ִ� ���� �迭 file�� �Է�*/
				if (fscanf(fp, "%s %lf", file[k].name, &file[k].score) == EOF)
					break;
		}

		fclose(fp);											/*���� �ݱ�*/
	}

	if ((fp = fopen("score.txt", "w")) == NULL)				/*���� ���� score.txt����*/
	{
		printf("������ ������ �ʽ��ϴ�.\n");
		exit(1);
	}
	gotoxy(30, 20);
	fputs("�̸� �Է�: ", stdout);
	gets(file[k].name);										/*�̸� �Է� �ް�*/
	file[k].score = score;									/*���� ����*/
	k++;
	
	for (i = 1; i < k; i++)									/*score.txt���� �޾ƿ� ���� ���ο� �̸�, ������ �������ķ� ����*/
	{
		save = file[i];
		for (j = i - 1; j >= 0 && file[j].score < file[j + 1].score; j--)
		{
			file[j + 1] = file[j];
			file[j] = save;
		}
	}

	for (i = k - 1; i >= 0; i--)								/*�ִ� 10���� �������� ���Ͽ� ����*/
		fprintf(fp, "%s %lf\n", file[i].name, file[i].score);

	fclose(fp);												/*���� �ݱ�*/
	print_score();											/*���� ��� �Լ�*/
}

void print_score()											/*���� ��� �Լ�*/
{
	FILE * fp;
	save score[10] = { NULL };								/*���� ����� ���� ����ü �迭*/
	int i, j, y = 4;
	int min;
	double sec;
	system("cls");
	gotoxy(30, y);
	printf("����\t�̸�\t�ð�\n");
	if ((fp = fopen("score.txt", "r")) == NULL)				/*�б� ���� score.txt���� ����*/
	{
		printf("������ �����ϴ�.\n");
		exit(1);
	}

	for (i = 0; i < 10; i++)								/*�迭 score�� score.txt���� �о�� �� ����*/
	{
		fscanf(fp, "%s %lf", score[i].name, &score[i].score);
		if (strcmp(score[i].name, "0.0") == 0 && score[i].score == 0.0)
			break;
	}

	for (j = 0; j < i; j++)									/*�迭 score ���*/
	{
		gotoxy(30, y + (j + 1) * 2);

		min = (int)score[j].score / 60;
		sec = score[j].score - min*60;

		printf("%d.\t%s\t%d:%.2lf\n", j + 1, score[j].name, min, sec);
	}
	Sleep(5000);											/*5�� ����*/

	fclose(fp);												/*���� �ݱ�*/
}

void shadow(int loc_arr[row][col])
{
	int i, j;
	Loc_arr loc_arr_b;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
			loc_arr_b.loc_arr[i][j] = loc_arr[i][j];
	}

	for (i = row - 1; i >= 0; i--)
	{
		for (j = 1; j < col; j++)
		{
			if (loc_arr[i][j] == 6)
				loc_arr[i][j] = 0;
		}
	}
	
	while ((ground(loc_arr_b.loc_arr) != -1 && s_block(loc_arr_b.loc_arr) != 0))
		down_block(loc_arr_b.loc_arr);
		
	

	for (i = row - 1; i >= 0; i--)
	{
		for (j = 1; j < col; j++)
		{
			if (loc_arr_b.loc_arr[i][j] == 1 && loc_arr[i][j] != 1)
			{
				loc_arr[i][j] = 6;
				loc_arr_b.loc_arr[i][j] = 0;
			}
		}
	}
}

void gameplay_2()
{
	int rand_num1 = sel_block(), rand_num2 = rand_num1;
	int rotation = 0;
	char cursor = NULL;
	int arr_row = 0, arr_col = col / 2;
	int x1, y1, x2, y2;
	int move1, move2, full1 = 0, full2 =0;
	int time = 0, lev1 = 20000, lev2 = 20000;
	int end1 = 0, end2 = 0;
	int next_block1, next_block2;
	int top1, top2;
	int toss1[10], toss2[10];

	// 2��° ������ ���
	next_block1 = rand() % 7;
	next_block2 = rand() % 7;

	Loc_arr loc_arr1;
	Loc_arr loc_arr2;
	Loc_arr loc_arr_b1;
	Loc_arr loc_arr_b2;

	// 1p ���� ����, ��� ���
	set_line(loc_arr1.loc_arr);
	print_line(loc_arr1.loc_arr, 8, 2);
	next_block_line_print(36, 4);
	put_block(loc_arr1.loc_arr, rand_num1, rotation, arr_row, arr_col);
	next_block_print(38, 6, next_block1);

	// 2p ���� ����, ��� ���
	set_line(loc_arr2.loc_arr);
	print_line(loc_arr2.loc_arr, 50, 2);
	next_block_line_print(76, 4);
	put_block(loc_arr2.loc_arr, rand_num2, rotation, arr_row, arr_col);
	next_block_print(78, 6, next_block2);

	// ���� ����
	while (1) {
		move1 = -1, move2 = -1;
		x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		full1 = 0, full2 = 0;
		
		// 1p, 2p Ű �Է�
		if (kbhit())
		{
			cursor = getch();
			// 1p �� ����ϴ� Ű �Է½�
			if(cursor == UP || cursor == DOWN || cursor == LEFT || cursor == RIGHT || cursor == SP)
				move1 = key_control(cursor, &x1, &y1, &rotation, loc_arr1.loc_arr);
			// 2p �� ����ϴ� Ű �Է½�
			else if(cursor == W || cursor == S || cursor == A || cursor == D || cursor == V)
				move2 = key_control2(cursor, &x2, &y2, &rotation, loc_arr2.loc_arr);
		}

		// 1p, 2p ��� �̵�
		if (move1 == 1)
			move_block(loc_arr1.loc_arr, x1, y1);
		if (move2 == 1)
			move_block(loc_arr2.loc_arr, x2, y2);
		
		// 1p, 2p ��� ȸ��
		if (move1 == 2)
			rotate(loc_arr1.loc_arr, x1, y1, rand_num1, rotation);
		if (move2 == 2)
			rotate(loc_arr2.loc_arr, x2, y2, rand_num2, rotation);

		// 1p, 2p ��� ���, ���
		print_block(loc_arr1.loc_arr, loc_arr_b1.loc_arr, move1, 6, 2);
		backup_block(loc_arr1.loc_arr, loc_arr_b1.loc_arr);
		print_block(loc_arr2.loc_arr, loc_arr_b2.loc_arr, move2, 48, 2);
		backup_block(loc_arr2.loc_arr, loc_arr_b2.loc_arr);

		// 1p, 2p ������ á���� Ȯ��
		full1 = line_full(loc_arr1.loc_arr);
		full2 = line_full(loc_arr2.loc_arr);
		
		// 1p, 2p ������ �� �� ���
		if (full1)
		{
			top1 = search_top(loc_arr1.loc_arr, full1);
			top2 = search_top(loc_arr2.loc_arr, full2);
			save_line(loc_arr1.loc_arr, toss1, full1);
			delete_line(loc_arr1.loc_arr, full1, top1);
			toss_line(loc_arr2.loc_arr, toss1, top2);
			lev1 -= 50;
		}

		if (full2)
		{
			top1 = search_top(loc_arr1.loc_arr, full1);
			top2 = search_top(loc_arr2.loc_arr, full2);
			save_line(loc_arr2.loc_arr, toss2, full2);
			delete_line(loc_arr2.loc_arr, full2, top2);
			toss_line(loc_arr1.loc_arr, toss2, top1);
			lev2 -= 50;
		}

		// 1p, 2p ����� �ٴ�, ������Ͽ� ����� ���
		if (((ground(loc_arr1.loc_arr) == -1 || s_block(loc_arr1.loc_arr) == 0) && time % 10000 == 0) || move1 == 3)
		{
			block_ground(loc_arr1.loc_arr);
			rotation = 0;
			rand_num1 = next_block1;
			end1 = put_block(loc_arr1.loc_arr, rand_num1, rotation, arr_row, arr_col);
			if (end1 == -1)
				break;
			next_block1 = sel_block();
			next_block_print(38, 6, next_block1);
		}

		if (((ground(loc_arr2.loc_arr) == -1 || s_block(loc_arr2.loc_arr) == 0) && time % 10000 == 0) || move2 == 3)
		{
			block_ground(loc_arr2.loc_arr);
			rotation = 0;
			rand_num2 = next_block2;
			end2 = put_block(loc_arr2.loc_arr, rand_num2, rotation, arr_row, arr_col);
			if (end2 == -1)
				break;
			next_block2 = sel_block();
			next_block_print(78, 6, next_block2);
		}
		
		// 1p, 2p �׸���
		shadow(loc_arr1.loc_arr); 
		shadow(loc_arr2.loc_arr);
		
		// 1p, 2p �ð��� ������ ����� ������
		if (time % lev1 == 0)
			down_block(loc_arr1.loc_arr);
		if (time % lev2 == 0)
			down_block(loc_arr2.loc_arr);

		time += 2;
	}

	system("cls");

	// 2p �¸�
	if (end1 == -1)
	{
		gotoxy(43, 15);
		printf("2P �¸�");
		Sleep(3000);
	}
	
	// 1p �¸�
	if (end2 == -1)
	{
		gotoxy(43, 15);
		printf("1P �¸�");
		Sleep(3000);
	}
}

int key_control2(char cursor, int *x, int *y, int *rotation, int loc_arr[row][col])
{
	switch (cursor)
	{
	case W:
		if (*rotation == 3)
			*rotation = 0;
		else
			(*rotation) += 1;
		return 2;

	case S:
		if (ground(loc_arr) != -1 && s_block(loc_arr) != 0)
			*y += 1;
		return 1;

	case A:
		if (wall(loc_arr) != -1 && s_block_rl(loc_arr) != -1)
			*x -= 1;
		return 1;

	case D:
		if (wall(loc_arr) != 1 && s_block_rl(loc_arr) != 1)
			*x += 1;
		return 1;
	case V:
		SPbar(loc_arr);
		return 3;
	}
	return 0;
}