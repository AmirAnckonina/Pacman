#pragma once
using namespace std;

#include "Windows.h"
#include <iostream>
#include <conio.h>
#include <cstring>
#include <Windows.h>

enum gameColors { WHITE = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, YELLOW = 5, BLACK = 6 };
const char SPACE = ' ', BORDER = 219, BREADCRUMB = '*', TUNNEL = '|';
enum gameKeys { UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100, STAY = 115, WRONG_KEY = -1, ESC = 27 };
//const int WRONG_KEY = -1;

class Utilities
{
public:
	//void setTextColor(int c);
	static void gotoxy(int x = 1, int y = 1);
};