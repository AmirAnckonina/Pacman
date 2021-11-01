#pragma once

using namespace std;
#include "Point.h"
#include <iostream>
#include <cstring>
#include "GameBoard.h"
#include <conio.h>
#include <windows.h>

class Pacman
{
	int startingX = 1;
	int startingY = 1;
	Point startingPoint;

	const char PacmanArtifact = '@';
	enum directions { UP = 119, DOWN = 115, LEFT = 97, RIGHT = 100 };

public:
	void setPacman()
	{
		startingPoint.gotoxy();
	}
	void movePacman();


};