#pragma once

#include <iostream>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include "Windows.h"
#include <time.h>

using std::cout;
using std::endl;

enum class Colors {
	BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, BROWN = 6, GRAY = 8
	, LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11, LIGHTRED = 12
	, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15
};

//Global functions
void gotoxy(int x = 1, int y = 1);
void setTextColor(Colors c);
void hideCursor();
void resetColors();
void clearInput();
void clearScreen();