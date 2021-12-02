#pragma once
#include"Utilities.h"
#include "Position.h"
#include"GameBoard.h"

class Creature
{
	Colors creatureColor = Colors::WHITE;
	Position currPos, nextPos;
	Direction creatureDirection;

public:
	void initCreature();
	void moveCreature(GameBoard& board);

	void updatePos() { currPos = nextPos; };

	//Get-Set Functions
	void setCreaturePosition();
	void setDirection(Direction dir);

	Position getCurrPos() const { return currPos; }
	Direction getDirection(char key) const;




};
