#pragma once
//using namespace std;

#include "Windows.h"
#include "GameBoard.h"
#include "Utilities.h"
using std::cout;
using std::endl;
class GameBoard; //Forward declaraion.
class Position
{

private:
	int _x = 1, _y = 1;

public:
	//C'tor
	Position(int x = 1, int y = 1) { _x = x; _y = y; }

	//Get-Set.
	void setXPos(int x = 1) { _x = x; }
	void setYPos(int y = 1) { _y = y; }
	int getXPos() const { return _x; }
	int getYPos() const { return _y; }

	//Others

	bool isPositionValid(GameBoard& board, char figure);
	void setNextPos(Direction dir, char figure);

};