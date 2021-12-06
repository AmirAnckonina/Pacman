#include "Creature.h"

Creature::Creature(Colors _creatureColor, Position _currPos, Position _nextPos, Direction _creatureDirection, char _figure)
	: creatureColor(_creatureColor), currPos(_currPos), nextPos(_nextPos), creatureDirection(_creatureDirection), figure(_figure){}

void Creature::initCreature()
{
	creatureColor = Colors::WHITE;
	setCreaturePosition();
}
void Creature::setCreaturePosition()
{
	currPos.setXPos();
	currPos.setYPos();
	nextPos = currPos;
}

void Creature::setCreatureNextPos()
{
	nextPos.setNextPos(creatureDirection, figure);
}
