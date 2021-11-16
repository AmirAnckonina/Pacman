#pragma once
using namespace std;

#include "Windows.h"
#include <iostream>
#include <conio.h>
#include <cstring>
#include <Windows.h>

enum class gameColors { BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, BROWN = 6 
	,LIGHTBLUE	= 9 ,LIGHTGREEN	= 10, LIGHTCYAN = 11, LIGHTRED = 12 
	,LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15 };
enum class gameKeys { UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100, STAY = 115, WRONG_KEY = -1, ESC = 27 };

const char SPACE = ' ', BORDER = 219, BREADCRUMB = '*', TUNNEL = '|';
const char START = 1, STARTCOLORIZED = 2, INSTRUCTIONS = 8, EXIT = 9 ;

void gotoxy(int x = 1, int y = 1);
void setTextColor(gameColors c);
void hideCursor();
void resetColors();
