#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "GameBoard.h"

using std::cout;
using std::endl;

//enum class Colors;
class GameBoard; //Forward declaraion.
class Position
{

private:
	int x = 1, y = 1;

public:
	//C'tor
	Position(int _x = 1, int _y = 1) { x = _x; y = _y; }

	bool isPositionValid(GameBoard& board, char figure);
	void setNextPos(Direction dir, char figure, GameBoard& board);

	//Get-Set functions
	int getXPos() const { return x; }
	int getYPos() const { return y; }
	void setXPos(int _x = 1) { x = _x; }
	void setYPos(int _y = 1) { y = _y; }
};