#pragma once
//using namespace std;

#include "Utilities.h"
#include "Position.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include "GameBoard.h"
#include <conio.h>
#include <windows.h>
using std::cout;
using std::endl;
class Ghost
{
	//public:
	//	enum directions { UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100, STAY = 115 };

private:
	const char ghostFigure = '$';
	gameColors ghostColor = gameColors::WHITE;
	Position currPos, nextPos;
	Direction ghDirecrtion;

public:
	void setGhostColor(gameColors color) { ghostColor = color; }
	gameColors getGhostColor() { return ghostColor; }

	Position getCurrPos() { return currPos; }
	void moveGhost(GameBoard& board);
	void initGhost(int xCoord, int yCoord);
	void setGhostLocation(int xCoord, int yCoord);
	void updatePos() { currPos = nextPos; };
	void setRandomDirection();
	void printGhost();
};