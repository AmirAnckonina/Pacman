#pragma once

using namespace std;

#include "Position.h"
#include "GameBoard.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Utilities.h"

class Pacman
{

private:
	int livesLeft = 3;
	int score = 0;
	Position currPos, nextPos;
	const char pacmanFigure = '@';
	enum directions { UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100, STAY = 115 };
	int pacDirection = 115; //Direction Saver might not necessary?

public:
	//Get-Set
	Position getCurrPos() { return currPos; }
	char getDirection(char key) const;
	void setDirection(int direction);
	int getScore() const { return score; }
	void setLivesLeft() { livesLeft--; }
	int getLivesLeft() { return livesLeft; }

	//Others
	void setPacman(); //Not good - currPos.setXPos(1); currPos.setYPos(1); }
	void resetPacman();
	void movePacman(GameBoard& board);
	void updatePos() { currPos = nextPos; };
	void updateScore(GameBoard& board);
	void printPacman();
};
