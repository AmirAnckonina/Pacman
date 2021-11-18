#pragma once

#include "Utilities.h"
#include "Position.h"
#include "GameBoard.h"

using std::cout;
using std::endl;

class Ghost
{

private:
	const char ghostFigure = GHOST;
	gameColors ghostColor = gameColors::WHITE;
	Position currPos, nextPos;
	Direction ghostDirection;

public:

	void setGhostColor(gameColors color) { ghostColor = color; }
	void moveGhost(GameBoard& board);
	void initGhost(int xCoord, int yCoord);
	void setGhostPosition(int xCoord, int yCoord);
	void updatePos() { currPos = nextPos; };
	void setRandomDirection();

	gameColors getGhostColor() const { return ghostColor; }
	Position getCurrPos() const { return currPos; }
	void printGhost() const;
};