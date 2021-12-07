#pragma once
#include <queue>
#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"

using std::queue;

using std::cout;
using std::endl;

class Ghost :public Creature
{
public:
	static constexpr char GHOST = '$';
	//private:
		//Colors ghostColor = Colors::WHITE;
		//Position currPos, nextPos;
		//Direction ghostDirection;

public:
	Ghost() {};
	Ghost(Position _ghostCurrPos, Position _ghostNextPos, Direction _ghostDirection = Direction::STAY, Colors _ghostColor = Colors::WHITE, char _ghostIcon = '$');
	void initGhost();
	void moveGhost(GameBoard& board);
	//void updatePos() { currPos = nextPos; };
	//void printGhost() const;

	//Get-Set functions
	//void setGhostPosition(int xCoord, int yCoord);
	void generateRandomDirection();
	//void setGhostColor(Colors color) { ghostColor = color; }
	//Colors getGhostColor() const { return ghostColor; }
	//Position getCurrPos() const { return currPos; }

	void smartGhostMove();
};