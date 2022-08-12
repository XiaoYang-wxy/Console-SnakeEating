#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include <string>
#include <tchar.h>

using std::cin;
using std::cout;
using std::string;

const int M = 30, N = 30, max_score = 20, start_length = 3, sleep = 200;
const string head = "●", body = "○", food = "★", wall = "■", land = "▓ ";

void gotoxy(short, short);
void initial();
class state
{
private:
	short length, snake[(M - 2) * (N - 2)][2];
	char direction, food[2];
	void food_restart();//重新生成食物，不与蛇身重合
public:
	state();
	friend int remove(state*, char);//蛇移动
	friend int judge(state*);//判断蛇是否越界或者吃到自己
	friend void putout_snake(state*, int);//蛇移动后重新绘制蛇
	friend void level_mode(state*);//关卡模式，分数有上限
	friend void endless_mode(state*);//无尽模式，分数无上限
};
