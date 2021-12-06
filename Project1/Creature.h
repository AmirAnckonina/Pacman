#pragma once
#include"Utilities.h"
#include "Position.h"
#include"GameBoard.h"

class Creature
{
	char creatureIcon;
	Position startingPos ,currPos, nextPos;
	Direction creatureDirection;
	Colors creatureColor = Colors::WHITE;

public:
	Creature() {};
	Creature(Colors _creatureColor, Position _currPos, Position _nextPos, Direction _creatureDirection, char _creatureIcon);

	void moveCreature(GameBoard& board);
	void updatePos() { currPos = nextPos; }
	void resetNextPos() { nextPos = currPos; }

	//Get-Set Functions
	void resetCreaturePosition();

	void setStartingPos(Position _startingPos) { startingPos = _startingPos; }
	Position getStartingPos() const { return startingPos; }
	void setCurrPos(Position _currPos) { currPos = _currPos; }
	Position getCurrPos() const { return currPos; }
	void setNextPos(Position _nextPos) { nextPos = _nextPos; }
	void setCreatureNextPos();
	Position getNextPos() const { return nextPos; }

	void setDirection(Direction _creatureDirection) { creatureDirection = _creatureDirection; }
	Direction getDirection() const { return creatureDirection; }

	void setColor(Colors _creatureColor) { creatureColor = _creatureColor; }
	Colors getColor() const { return creatureColor; }

	void setIcon(char _creatureIcon) { creatureIcon = _creatureIcon; }
	char getIcon() const { return creatureIcon; }

	bool isCreaturePositionValid(GameBoard& board);
};
