#include "state.h"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
int main()
{
	POINT* pt = new POINT;
	HWND hw = GetConsoleWindow();          //将当前控制台窗口的句柄赋值给hw
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);   //将控制台窗口输出缓冲区的句柄赋值给handle
  
	CONSOLE_CURSOR_INFO CursorInfo;                         //这四行代码可以隐藏控制台窗口光标
	GetConsoleCursorInfo(handle, &CursorInfo);              //    获取光标信息
	CursorInfo.bVisible = false;                            //    将光标修改为隐藏状态
	SetConsoleCursorInfo(handle, &CursorInfo);              //    应用光标信息
  
	DWORD Mode;                            //这五行代码可以调整控制台输出缓冲区的部分属性
	GetConsoleMode(handle, &Mode);         //    获取输出缓冲区属性
	Mode &= ~ENABLE_QUICK_EDIT_MODE;       //    关闭快速编辑模式
	Mode &= ~ENABLE_INSERT_MODE;           //    关闭插入模式
	SetConsoleMode(handle, Mode);          //    应用输出缓冲区属性
  
	SetWindowLongPtrA(
		hw, GWL_STYLE, GetWindowLongPtrA(hw, GWL_STYLE)
		& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX
	);             //这个函数可以保证控制台窗口大小固定不变
  
	system("mode con cols=97 lines=30");        //这个函数确定了控制台窗口大小
  
restart:;
	state* a = new state;
	string mode;
	int k = 0;
	initial();
	putout_snake(a, 0);
	for (;;)
		if (KEY_DOWN(VK_LBUTTON))   //如果鼠标左键被按下
		{
			GetCursorPos(pt);
			if (ScreenToClient(hw, pt))
				if (pt->x >= 584 && pt->x <= 686 && pt->y >= 168 && pt->y <= 198)
				{
					mode = "level";
					break;
				}
				else if (pt->x >= 584 && pt->x <= 686 && pt->y >= 232 && pt->y <= 261)
				{
					mode = "endless";
					break;
				}
		}
	if (mode == "level")
		level_mode(a);
	else if (mode == "endless")
		endless_mode(a);
	gotoxy(M * 2, 21);
	cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
	gotoxy(M * 2, 22);
	cout << "   ┍━━━━━━━━━┑       ┍━━━━━┑";
	gotoxy(M * 2, 23);
	cout << "   │ 返回首页│       │ 退出│";
	gotoxy(M * 2, 24);
	cout << "   ┕━━━━━━━━━┙       ┕━━━━━┙";
	gotoxy(M * 2, 25);
noexit:;
	for (;;)
		if (KEY_DOWN(VK_LBUTTON))   //如果鼠标左键被按下
		{
			GetCursorPos(pt);
			if (ScreenToClient(hw, pt))
				if (pt->x >= 512 && pt->x <= 590 && pt->y >= 361 && pt->y <= 390)
				{
					k = 1;
					break;
				}
				else if (pt->x >= 656 && pt->x <= 701 && pt->y >= 361 && pt->y <= 390)
					break;
		}
	if (k == 1)
	{
		system("cls");
		delete a, k, mode;
		goto restart;
	}
	k = MessageBox(hw, _T("                             确认退出？"), _T(" "), MB_YESNO | MB_APPLMODAL);
	if (k == 7)
	{
		goto noexit;
	}
	return 0;
}
