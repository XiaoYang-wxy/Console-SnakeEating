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

void gotoxy(short, short);//移动光标到相对窗口(x,y)坐标的位置
void initial();//初始化界面函数
class state
{
private:
	short length, snake[(M - 2) * (N - 2)][2], food[2];//蛇长度，蛇坐标，食物坐标
	char direction;//移动方向，有wasd四种方向
	void food_restart();//重新生成食物，不与蛇身重合
public:
	state();
	friend int remove(state*, char);//蛇移动
	friend int judge(state*);//判断蛇是否越界或者吃到自己
	friend void putout_snake(state*, int);//蛇移动后重新绘制蛇
	friend void level_mode(state*);//关卡模式，分数有上限
	friend void endless_mode(state*);//无尽模式，分数无上限
};
