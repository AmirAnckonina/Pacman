#include "Creature.h"

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
