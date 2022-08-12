#include "state.h"
std::random_device rd;

//移动光标函数
void gotoxy(short x, short y)
{
	_COORD position = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, position);
}

//初始化界面函数
void initial()
{
	for (short i = 0; i < M * 2; i += 2)
	{
		gotoxy(i, 0);
		cout << wall;
	}
	for (short i = 1; i < N; i++)
	{
		gotoxy(0, i);
		cout << wall;
	}
	for (short i = 1; i < N; i++)
	{
		gotoxy(M * 2 - 2, i);
		cout << wall;
	}
	for (short i = 0; i < M * 2; i += 2)
	{
		gotoxy(i, N - 1);
		cout << wall;
	}
	for (short i = 2; i < M * 2 - 2; i += 2)
		for (short j = 1; j < N - 1; j++)
		{
			gotoxy(i, j);
			cout << land;
		}
	gotoxy(M * 2, 1);
	cout << "     游戏名称：贪吃蛇进阶版";
	gotoxy(M * 2, 2);
	cout << "         作者：王晓阳";
	gotoxy(M * 2, 3);
	cout << "                  W";
	gotoxy(M * 2, 4);
	cout << "         玩法： A S D 控制方向";
	gotoxy(M * 2, 5);
	cout << "                space 暂停";
	gotoxy(M * 2, 6);
	cout << "         不要撞到墙或吃到自己！";
	gotoxy(M * 2, 8);
	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
	gotoxy(M * 2, 10);
	cout << "            ┍━━━━━━━━━━━━┑";
	gotoxy(M * 2, 11);
	cout << "            │  关卡模式  │";
	gotoxy(M * 2, 12);
	cout << "            ┕━━━━━━━━━━━━┙";
	gotoxy(M * 2, 14);
	cout << "            ┍━━━━━━━━━━━━┑";
	gotoxy(M * 2, 15);
	cout << "            │  无尽模式  │";
	gotoxy(M * 2, 16);
	cout << "            ┕━━━━━━━━━━━━┙";
}

state::state()
{
	length = start_length;
	for (short i = 0; i <= start_length - 1; i++)
	{
		snake[i][0] = start_length + 1 - i, snake[i][1] = 2;
	}
	snake[start_length][0] = 1, snake[start_length][1] = 1;
	direction = 'd';
	food[0] = rd() % (M - 4) + 2, food[1] = rd() % (N - 5) + 3;
}

//重新生成食物函数，可以保证食物不与蛇重合
void state::food_restart()
{
	int m, n;
	for (;;)
	{
		int k = 0;
		m = rd() % (M - 2) + 1, n = rd() % (N - 2) + 1;
		for (int i = 0; i < length; i++)
		{
			if (snake[i][0] == m && snake[i][1] == n)
			{
				k = 1;
				break;
			}
		}
		if (k == 0)
			break;
	}
	food[0] = m, food[1] = n;
}

//蛇移动函数
int remove(state* a, char c)
{
	int headw = a->snake[0][0], headh = a->snake[0][1];
	if (c == 'w' && a->direction != 's' && a->direction != 'w')
	{
		a->snake[0][1] -= 1;
		a->direction = 'w';
	}
	else if (c == 's' && a->direction != 's' && a->direction != 'w')
	{
		a->snake[0][1] += 1;
		a->direction = 's';
	}
	else if (c == 'a' && a->direction != 'a' && a->direction != 'd')
	{
		a->snake[0][0] -= 1;
		a->direction = 'a';
	}
	else if (c == 'd' && a->direction != 'a' && a->direction != 'd')
	{
		a->snake[0][0] += 1;
		a->direction = 'd';
	}
	else if (a->direction == 'w')
		a->snake[0][1] -= 1;
	else if (a->direction == 's')
		a->snake[0][1] += 1;
	else if (a->direction == 'a')
		a->snake[0][0] -= 1;
	else if (a->direction == 'd')
		a->snake[0][0] += 1;
	for (int i = a->length; i >= 2; i--)
	{
		a->snake[i][0] = a->snake[i - 1][0];
		a->snake[i][1] = a->snake[i - 1][1];
	}
	a->snake[1][0] = headw, a->snake[1][1] = headh;
	if (a->snake[0][0] == a->food[0] && a->snake[0][1] == a->food[1])
	{
		a->length += 1;
		a->food_restart();
		return 1;
	}
	else
		return 0;
}

//判断蛇是否越界或者吃到自己
int judge(state* a)
{
	int k = 0;
	if (a->length == max_score + start_length)
		k = 2;
	for (int i = 0; i < a->length; i++)
	{
		if (a->snake[i][0] == 0 || a->snake[i][0] == M - 1 || a->snake[i][1] == 0 || a->snake[i][1] == N - 1)
		{
			k = 1;
			break;
		}
		else if (i != 0 && a->snake[0][0] == a->snake[i][0] && a->snake[0][1] == a->snake[i][1])
		{
			k = 1;
			break;
		}
	}
	return k;
}

//蛇移动后重新绘制蛇
void putout_snake(state* a, int eat)
{
	gotoxy(2 * a->food[0], a->food[1]);
	cout << food;
	for (short i = 1; i < a->length; i++)
	{
		gotoxy(2 * a->snake[i][0], a->snake[i][1]);
		cout << body;
	}
	if (!eat)
	{
		gotoxy(2 * a->snake[a->length][0], a->snake[a->length][1]);
		cout << land;
	}
	gotoxy(2 * a->snake[0][0], a->snake[0][1]);
	cout << head;
	gotoxy(M * 2, 25);
}

//关卡模式，得到20分即通关
void level_mode(state* a)
{
	int eat = 0;
	char pause;
	gotoxy(M * 2, 10);
	cout << "                           ";
	gotoxy(M * 2, 11);
	cout << "           当前分数：" << a->length - start_length << "     ";
	gotoxy(M * 2, 12);
	cout << "                           ";
	gotoxy(M * 2, 14);
	cout << "           目标得分：" << max_score << "     ";
	gotoxy(M * 2, 15);
	cout << "                           ";
	gotoxy(M * 2, 16);
	cout << "                           ";
	for (; _kbhit();)
		pause = _getch();
	gotoxy(M * 2, 18);
	cout << "按任意键开始";
	pause = _getch();
	gotoxy(M * 2, 18);
	cout << "              ";
	for (char c;;)
	{
		Sleep(sleep);
		c = NULL;
		if (_kbhit())
			c = _getch();
		if (c == ' ')
		{
			gotoxy(M * 2, 18);
			cout << "已暂停，按任意键继续";
			pause = _getch();
			gotoxy(M * 2, 18);
			cout << "                      ";
		}
		eat = remove(a, c);
		putout_snake(a, eat);
		gotoxy(M * 2, 11);
		cout << "           当前分数：" << a->length - start_length << "     ";
		if (judge(a) == 1 || judge(a) == 2)
		{
			if (judge(a) == 1)
			{
				gotoxy(M * 2, 18);
				cout << "               失败！";
			}
			else if (judge(a) == 2)
			{
				gotoxy(2 * a->food[0], a->food[1]);
				cout << land;
				gotoxy(M * 2, 18);
				cout << "             恭喜通关！";
			}
			break;
		}
	}
}

//无尽模式，蛇长度无上限
void endless_mode(state* a)
{
	int eat = 0;
	char pause;
	gotoxy(M * 2, 10);
	cout << "                           ";
	gotoxy(M * 2, 11);
	cout << "                           ";
	gotoxy(M * 2, 12);
	cout << "           当前分数：" << a->length - start_length << "     ";
	gotoxy(M * 2, 14);
	cout << "                           ";
	gotoxy(M * 2, 15);
	cout << "                           ";
	gotoxy(M * 2, 16);
	cout << "                           ";
	for (; _kbhit();)
		pause = _getch();
	gotoxy(M * 2, 18);
	cout << "按任意键开始";
	pause = _getch();
	gotoxy(M * 2, 18);
	cout << "              ";
	for (char c;;)
	{
		Sleep(sleep);
		c = NULL;
		if (_kbhit())
			c = _getch();
		if (c == ' ')
		{
			gotoxy(M * 2, 18);
			cout << "已暂停，按任意键继续";
			pause = _getch();
			gotoxy(M * 2, 18);
			cout << "                      ";
		}
		eat = remove(a, c);
		putout_snake(a, eat);
		gotoxy(M * 2, 12);
		cout << "           当前分数：" << a->length - start_length << "     ";
		if (judge(a) == 1)
		{
			gotoxy(M * 2, 18);
			cout << "               失败！";
			break;
		}
	}
}
