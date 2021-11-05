// Pacman.h

#pragma once

using namespace std;
#include "Point.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "GameBoard.h"
#include <conio.h>
#include <windows.h>

class Pacman
{
	int startingX = 1;
	int startingY = 1;
	int currXInd;
	int score = 0;
	int currYind;
	char currUserDirection;
	Point startingPoint, currPoint;
	GameBoard board;
	const char PacmanArtifact = '@';
	enum directions { UP = 119, DOWN = 115, LEFT = 97, RIGHT = 100 };

public:
	void updateBoard();
	bool isMoveValid();
	void setPacman()
	{
		startingPoint.printPoint(startingX, startingY);
		startingPoint.gotoxy();
	}
	void movePacman(int currX, int currY);


};