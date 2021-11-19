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
	Colors ghostColor = Colors::WHITE;
	Position currPos, nextPos;
	Direction ghostDirection;

public:

	void setGhostColor(Colors color) { ghostColor = color; }
	void moveGhost(GameBoard& board);
	void initGhost(int xCoord, int yCoord);
	void setGhostPosition(int xCoord, int yCoord);
	void updatePos() { currPos = nextPos; };
	void setRandomDirection();

	Colors getGhostColor() const { return ghostColor; }
	Position getCurrPos() const { return currPos; }
	void printGhost() const;
};