#pragma once
using namespace std;
#include "Position.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include "GameBoard.h"
#include <conio.h>
#include <windows.h>

class Ghost
{
	//public:
	//	enum directions { UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100, STAY = 115 };

private:
	const char ghostFigure = '$';
	Position currPos, nextPos;
	int ghDirecrtion;

public:
	Position getCurrPos() { return currPos; }
	void moveGhost(GameBoard& board);
	void setGhost(int xCoord, int yCoord);
	void updatePos() { currPos = nextPos; };
	void setRandomDirection();
	void printGhost();
};