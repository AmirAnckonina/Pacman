#pragma once

using namespace std;

#include "Utilities.h"
#include "Position.h"
#include "GameBoard.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include <windows.h>

class Pacman
{

private:
	const char pacmanFigure = '@';
	gameColors pacColor = WHITE;
	Position currPos, nextPos;
	Direction pacmanDirection = Direction::STAY; 
	int livesLeft = 3;
	int score = 0;

public:
	//Get-Set
	Position getCurrPos() { return currPos; }
	Direction getDirection(char key) const;
	void setDirection(Direction dir);
	int getScore() const { return score; }
	void setLivesLeft() { livesLeft--; }
	int getLivesLeft() { return livesLeft; }

	void setPacColor(gameColors color) { pacColor = color; }
	gameColors getPacColor() { return pacColor; }

	//Others
	void setPacman(); //Not good - currPos.setXPos(1); currPos.setYPos(1); }
	void resetPacman();
	void movePacman(GameBoard& board);
	void updatePos() { currPos = nextPos; };
	void updateScore(GameBoard& board);
	void printPacman();
};
