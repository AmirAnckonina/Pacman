#pragma once

using namespace std;
#include "Position.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "GameBoard.h"
#include <conio.h>
#include <windows.h>

class Pacman
{
public: //enum??? const??? should check about it.
	const int WRONG_KEY = -1;

private: //A little bit messy? we should arrange it again?
	int score = 0;
	Position currPos, nextPos;
	const char pacmanFigure = '@';
	enum directions { UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100 , STAY = 115 };
	int pacDirection = 115, directionSaver = 115; //Direction Saver might not necessary?

public:
	//Get-Set
	char getDirection(char key);
	void setDirection(int direction);
	int getScore() const { return score; }

	//Others
	void setPacman(GameBoard& board); //Not good - currPos.setXPos(1); currPos.setYPos(1); }
	void movePacman(GameBoard& board);
	void setNextPos();


};