#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"


using std::cout;
using std::endl;

class Ghost
{
public:
	static constexpr char GHOST = '$';
	//private:
		//Colors ghostColor = Colors::WHITE;
		//Position currPos, nextPos;
		//Direction ghostDirection;

public:

	//void initGhost(int xCoord, int yCoord);
	void moveGhost(GameBoard& board);
	//void updatePos() { currPos = nextPos; };
	//void printGhost() const;

	//Get-Set functions
	//void setGhostPosition(int xCoord, int yCoord);
	void generateRandomDirection();
	//void setGhostColor(Colors color) { ghostColor = color; }
	//Colors getGhostColor() const { return ghostColor; }
	//Position getCurrPos() const { return currPos; }
};