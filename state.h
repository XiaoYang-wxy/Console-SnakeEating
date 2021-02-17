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
	void food_restart();
public:
	state();
	friend int remove(state*, char);
	friend int judge(state*);
	friend void putout_snake(state*, int);
	friend void level_mode(state*);
	friend void endless_mode(state*);
};
