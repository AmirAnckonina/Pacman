#include "Creature.h"

Creature::Creature(Colors _creatureColor, Position _currPos, Position _nextPos, Direction _creatureDirection, char _creatureIcon)
	: creatureColor(_creatureColor), currPos(_currPos), nextPos(_nextPos), creatureDirection(_creatureDirection), creatureIcon(_creatureIcon){}

void Creature::initCreature()
{
	creatureColor = Colors::WHITE;
	setCreaturePosition();
}
void Creature::resetCreaturePosition()
{
	//currPos should changed to startingPos
	//NextPos should changed also to currPos
	currPos = startingPos;
	nextPos = currPos;
}

void Creature::setCreatureNextPos()
{
	nextPos.setNextPos(creatureDirection, creatureIcon);
}

bool Creature::isCreaturePositionValid(GameBoard& board)
{
	return nextPos.isPositionValid(board, creatureIcon);
}
