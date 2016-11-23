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

// ************ 라인 관련 함수 ******************
void set_line(int[row][col]);											/*테두리를 그리는 함수*/

// ************ 블록 관련 함수 ******************
int sel_block(void);													/*랜덤으로 나오는 블록을 정해주는 함수*/
void move_block(int[row][col], int, int);								/*블록을 이동시키는 함수*/
void print_block(int[row][col], int[row][col], int, int, int);			/*블록을 출력해주는 함수*/
void backup_block(int[row][col], int[row][col]);						/*이전과 다른 것만 출력하기 위해 백업하는 함수*/
int put_block(int[row][col], int, int, int, int);						/*블록을 게임판 배열에 넣는 함수*/
void down_block(int[row][col]);											/*블록이 한칸씩 내려오게 하는 함수*/
void shadow(int[row][col]);												/*그림자 기능*/
int rotate(int[row][col], int, int, int, int);							/*블록을 회전시키는 함수*/
void block_ground(int[row][col]);										/*블록을 고정 블록으로 바꾸는 함수*/

// ************ 블록 충돌 관련 함수 ******************
int ground(int[row][col]);												/*바닥에 블록이 닿으면 값을 반환하는 함수*/
int s_block(int[row][col]);												/*블록 밑이 고정 블록에 닿으면 값을 반환하는 함수*/
int s_block_rl(int[row][col]);											/*블록 옆이 고정 블록에 닿으면 값을 반환하는 함수*/
int wall(int[row][col]);												/*벽에 충돌시 값을 반환하는 함수*/

// ************ 메뉴 함수 ******************
void print_menu();														/*메뉴 출력 함수*/
int select_menu();														/*메뉴 선택 함수*/
void cursor_control(char, int *, int *);								/*메뉴 좌표 입력 함수*/

// ************ 출력 함수 ******************
void print_line(int[row][col], int, int);								/*테두리를 출력하는 함수*/
void next_block_line_print(int, int);									/*다음에 나올 블록 칸 그리는 함수*/
void next_block_print(int, int, int);									/*다음에 나올 블록 출력 함수*/

// ************ 키 입력 함수 ******************
int key_control(char, int*, int*, int*, int[row][col]);					/*키를 입력받아서 값은 반환하는 함수*/
int key_control2(char, int*, int*, int*, int[row][col]);				/*키를 입력받아서 값은 반환하는 함수, 2인용*/
void SPbar(int[row][col]);												/*스페이스바를 누르면 작동하는 함수*/

// ************ 게임 기능 함수 ******************
int line_full(int[row][col]);											/*한 줄이 꽉 차면 값을 반환하는 함수*/
int search_top(int[row][col], int);										/*현재 고정 블록 중 가장 높은 위치를 찾는 함수*/
int delete_line(int[row][col], int, int);	   	   	   	   	   	   	   	/*한 줄을 삭제하는 함수*/
void save_line(int[row][col], int[], int);								/*삭제되는 줄 저장하는 함수*/
void toss_line(int[row][col], int[], int);								/*삭제되는 줄을 상대편에게 보내는 함수*/
void gameplay_1();														/*혼자하기 모드*/
void gameplay_2();														/*2인 모드*/

// ************ 점수 함수 ******************
void save_score(double);												/*점수 정렬, 저장 함수*/
void print_score();														/*점수 출력 함수*/

void gotoxy(int, int);													/*좌표 이동 함수*/

char block[7][4][4][4] =
{ { { { 0, 0, 0, 0 },					//L 블록
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

{ { { 0, 0, 0, 0 },					//역 L 블록
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

{ { { 0, 0, 1, 0 },					//일자 블록
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

{ { { 0, 0, 0, 0 },					// ㅗ 블록
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
{ 0, 0, 0, 0 } } }
};

int xb, yb;

typedef struct loc_arr {												/*테트리스 게임판을 위한 구조체*/
	int loc_arr[row][col];
}Loc_arr;

typedef struct save {													/*점수 저장하기 위한 구조체*/
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
					printf("■");
				else if (loc_arr[i][j] == 3)
					printf("▣");
				else if (loc_arr[i][j] == 0)
					printf("  ");
				else if (loc_arr[i][j] == 6)
					printf("□");
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
				printf("▩");
			else if (loc_arr[i][j] == 5)
				printf("▩");
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
	int i, j, k, l, xp = 0, yp = 0, rv = 0;
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

	for (i = 0; i < row; i++)						/* 고정 블록 중 가장 높은 블록의 높이를 찾아 top에 저장하는 반복문*/
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

	for (i = full - 1; i > top; i--)				/*꽉찬 줄 윗줄 부터 top까지 한줄씩 내리는 반복문*/
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

	for (i = top - 1; i < row - 1; i++)				/*top부터 맨 아래 까지 한줄씩 올리는 반복문*/
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

	// 2번째로 나올 블록
	next_block = rand() % 7;

	clock_t start, finish;

	Loc_arr loc_arr;
	Loc_arr loc_arr_b;

	// 게임 라인, 블록 출력
	set_line(loc_arr.loc_arr);
	print_line(loc_arr.loc_arr, 8, 2);
	next_block_line_print(40, 4);
	put_block(loc_arr.loc_arr, rand_num, rotation, arr_row, arr_col);
	next_block_print(42, 6, next_block);

	// 게임 시작 
	start = clock();
	while (1) {
		gotoxy(42, 15);
		printf("남은 줄: %0d", line_cnt);
		move = -1;
		x = 0, y = 0;
		full = 0;

		// 키 입력 시
		if (kbhit())
		{
			cursor = getch();
			move = key_control(cursor, &x, &y, &rotation, loc_arr.loc_arr);
		}

		// 블록 이동
		if (move == 1)
			move_block(loc_arr.loc_arr, x, y);
		
		// 블록 회전
		if (move == 2)
			rotate(loc_arr.loc_arr, x, y, rand_num, rotation);
		
		// 블록 출력, 백업
		print_block(loc_arr.loc_arr, loc_arr_b.loc_arr, move, 6, 2);
		backup_block(loc_arr.loc_arr, loc_arr_b.loc_arr);

		// 한줄이 꽉 찼는지 확인
		full = line_full(loc_arr.loc_arr);

		// 한줄이 꽉 찬 경우
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

		// 블록이 바닥, 고정블록에 닿았을 경우
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

		// 그림자
		shadow(loc_arr.loc_arr);

		// 시간에 따라 블록이 내려옴
		if (time % lev == 0)
			down_block(loc_arr.loc_arr);

		time += 2;

		// 현재 진행 중인 게임 시간 출력
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

	// 게임 실패
	if (end == -1)
	{
		gotoxy(43, 15);
		printf("실패");
		Sleep(3000);
	}

	// 게임 성공
	else if (end == 1)
	{
		gotoxy(43, 14);
		printf("성공!");
		gotoxy(43, 15);
		printf("성공 시간: %d:%.2lf", min, sec);
		save_score(duration);
	}
}

void print_menu()
{
	gotoxy(35, 10);
	printf("테트리스");
	gotoxy(35, 12);
	printf("1. 1인 플레이");
	gotoxy(35, 14);
	printf("2. 2인 플레이");
	gotoxy(35, 16);
	printf("3. 기록 확인");
	gotoxy(35, 18);
	printf("4. 종료");
}

int select_menu()
{
	int x = 33, y = 12, space = 0;					/*x, y는 메뉴가 출력된 좌표*/
	char cursor;

	gotoxy(x, y);
	printf("☞");

	while (1)
	{
		cursor = getch();							/*키보드에서 입력 받음*/
		gotoxy(x, y);
		printf(" ");
		cursor_control(cursor, &y, &space);		/*키보드에서 입력 받은 cursor 값으로 y, space 값 변경*/

		if ((y > 18))								/*y값의 최대 값 설정*/
			y -= 2;

		else if (y < 12)							/*y값의 최소 값 설정*/
			y += 2;

		gotoxy(x, y);
		printf("☞");

		if (space == 1)								/*선택시 반복문 탈출*/
			break;
	}

	switch (y) {									/*y 값에 따라서 선택*/
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
	case UP:				/*방향키 위*/
		*y -= 2;
		break;

	case DOWN:
		*y += 2;			/*방향키 아래*/
		break;

	case SP:				/*스페이스 바*/
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
	printf("┏━━━━┓");
	gotoxy(x, y++);
	printf("┃        ┃");
	gotoxy(x, y++);
	printf("┃        ┃");
	gotoxy(x, y++);
	printf("┃        ┃");
	gotoxy(x, y++);
	printf("┃        ┃");
	gotoxy(x, y);
	printf("┗━━━━┛");
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
				printf("■");
			else
				printf("  ");
		}
	}
}

void save_score(double score)									/*점수 저장 함수*/
{

	FILE* fp;
	save file[11] = { NULL };								/*점수 정렬을 위한 구조체 배열*/
	save save;

	int i, j, k = 0;

	if ((fp = fopen("score.txt", "r")) == NULL);				/*읽기 모드로 score.txt 열기*/

	else {													/*파일이 있다면*/
		if (fp != NULL)
		{
			for (k = 0; k < 10; k++)						/*score.txt에 있는 값을 배열 file에 입력*/
				if (fscanf(fp, "%s %lf", file[k].name, &file[k].score) == EOF)
					break;
		}

		fclose(fp);											/*파일 닫기*/
	}

	if ((fp = fopen("score.txt", "w")) == NULL)				/*쓰기 모드로 score.txt열기*/
	{
		printf("파일이 열리지 않습니다.\n");
		exit(1);
	}
	gotoxy(30, 20);
	fputs("이름 입력: ", stdout);
	gets(file[k].name);										/*이름 입력 받고*/
	file[k].score = score;									/*점수 저장*/
	k++;
	
	for (i = 1; i < k; i++)									/*score.txt에서 받아온 값과 새로운 이름, 점수를 삽입정렬로 정렬*/
	{
		save = file[i];
		for (j = i - 1; j >= 0 && file[j].score < file[j + 1].score; j--)
		{
			file[j + 1] = file[j];
			file[j] = save;
		}
	}

	for (i = k - 1; i >= 0; i--)								/*최대 10개의 값까지만 파일에 저장*/
		fprintf(fp, "%s %lf\n", file[i].name, file[i].score);

	fclose(fp);												/*파일 닫기*/
	print_score();											/*점수 출력 함수*/
}

void print_score()											/*점수 출력 함수*/
{
	FILE * fp;
	save score[10] = { NULL };								/*점수 출력을 위한 구조체 배열*/
	int i, j, y = 4;
	int min;
	double sec;
	system("cls");
	gotoxy(30, y);
	printf("순위\t이름\t시간\n");
	if ((fp = fopen("score.txt", "r")) == NULL)				/*읽기 모드로 score.txt파일 열기*/
	{
		printf("파일이 없습니다.\n");
		exit(1);
	}

	for (i = 0; i < 10; i++)								/*배열 score에 score.txt에서 읽어온 값 저장*/
	{
		fscanf(fp, "%s %lf", score[i].name, &score[i].score);
		if (strcmp(score[i].name, "0.0") == 0 && score[i].score == 0.0)
			break;
	}

	for (j = 0; j < i; j++)									/*배열 score 출력*/
	{
		gotoxy(30, y + (j + 1) * 2);

		min = (int)score[j].score / 60;
		sec = score[j].score - min*60;

		printf("%d.\t%s\t%d:%.2lf\n", j + 1, score[j].name, min, sec);
	}
	Sleep(5000);											/*5초 유지*/

	fclose(fp);												/*파일 닫기*/
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

	// 2번째 나오는 블록
	next_block1 = rand() % 7;
	next_block2 = rand() % 7;

	Loc_arr loc_arr1;
	Loc_arr loc_arr2;
	Loc_arr loc_arr_b1;
	Loc_arr loc_arr_b2;

	// 1p 게임 라인, 블록 출력
	set_line(loc_arr1.loc_arr);
	print_line(loc_arr1.loc_arr, 8, 2);
	next_block_line_print(36, 4);
	put_block(loc_arr1.loc_arr, rand_num1, rotation, arr_row, arr_col);
	next_block_print(38, 6, next_block1);

	// 2p 게임 라인, 블록 출력
	set_line(loc_arr2.loc_arr);
	print_line(loc_arr2.loc_arr, 50, 2);
	next_block_line_print(76, 4);
	put_block(loc_arr2.loc_arr, rand_num2, rotation, arr_row, arr_col);
	next_block_print(78, 6, next_block2);

	// 게임 진행
	while (1) {
		move1 = -1, move2 = -1;
		x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		full1 = 0, full2 = 0;
		
		// 1p, 2p 키 입력
		if (kbhit())
		{
			cursor = getch();
			// 1p 가 사용하는 키 입력시
			if(cursor == UP || cursor == DOWN || cursor == LEFT || cursor == RIGHT || cursor == SP)
				move1 = key_control(cursor, &x1, &y1, &rotation, loc_arr1.loc_arr);
			// 2p 가 사용하는 키 입력시
			else if(cursor == W || cursor == S || cursor == A || cursor == D || cursor == V)
				move2 = key_control2(cursor, &x2, &y2, &rotation, loc_arr2.loc_arr);
		}

		// 1p, 2p 블록 이동
		if (move1 == 1)
			move_block(loc_arr1.loc_arr, x1, y1);
		if (move2 == 1)
			move_block(loc_arr2.loc_arr, x2, y2);
		
		// 1p, 2p 블록 회전
		if (move1 == 2)
			rotate(loc_arr1.loc_arr, x1, y1, rand_num1, rotation);
		if (move2 == 2)
			rotate(loc_arr2.loc_arr, x2, y2, rand_num2, rotation);

		// 1p, 2p 블록 출력, 백업
		print_block(loc_arr1.loc_arr, loc_arr_b1.loc_arr, move1, 6, 2);
		backup_block(loc_arr1.loc_arr, loc_arr_b1.loc_arr);
		print_block(loc_arr2.loc_arr, loc_arr_b2.loc_arr, move2, 48, 2);
		backup_block(loc_arr2.loc_arr, loc_arr_b2.loc_arr);

		// 1p, 2p 한줄이 찼는지 확인
		full1 = line_full(loc_arr1.loc_arr);
		full2 = line_full(loc_arr2.loc_arr);
		
		// 1p, 2p 한줄이 꽉 찬 경우
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

		// 1p, 2p 블록이 바닥, 고정블록에 닿았을 경우
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
		
		// 1p, 2p 그림자
		shadow(loc_arr1.loc_arr); 
		shadow(loc_arr2.loc_arr);
		
		// 1p, 2p 시간이 지나면 블록이 내려옴
		if (time % lev1 == 0)
			down_block(loc_arr1.loc_arr);
		if (time % lev2 == 0)
			down_block(loc_arr2.loc_arr);

		time += 2;
	}

	system("cls");

	// 2p 승리
	if (end1 == -1)
	{
		gotoxy(43, 15);
		printf("2P 승리");
		Sleep(3000);
	}
	
	// 1p 승리
	if (end2 == -1)
	{
		gotoxy(43, 15);
		printf("1P 승리");
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