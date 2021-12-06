#pragma once
#include"Utilities.h"
#include "Position.h"
#include"GameBoard.h"

class Creature
{
	char figure;
	Position currPos, nextPos;
	Direction creatureDirection;
	Colors creatureColor = Colors::WHITE;

public:
	Creature() {};
	Creature(Colors _creatureColor, Position _currPos, Position _nextPos, Direction _creatureDirection, char _figure);

	void moveCreature(GameBoard& board);
	void updatePos() { currPos = nextPos; }

	//Get-Set Functions
	void setCreaturePosition();

	void setCurrPos(Position _currPos) { currPos = _currPos; }
	Position getCurrPos() const { return currPos; }
	void setNextPos(Position _nextPos) { nextPos = _nextPos; }
	void setCreatureNextPos();
	Position getNextPos() const { return nextPos; }

	void setDirection(Direction _creatureDirection) { creatureDirection = _creatureDirection; }
	Direction getDirection() const { return creatureDirection; }

	void setColor(Colors _creatureColor) { creatureColor = _creatureColor; }
	Colors getColor() const { return creatureColor; }

};
