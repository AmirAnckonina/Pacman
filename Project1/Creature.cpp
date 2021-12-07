#include "Creature.h"
#include "ThePacmanGame.h"

Creature::Creature(Colors _creatureColor, Position _currPos, Position _nextPos, Direction _creatureDirection, char _creatureIcon)
	: creatureColor(_creatureColor), 
	currPos(_currPos),
	nextPos(_nextPos),
	creatureDirection(_creatureDirection),
	creatureIcon(_creatureIcon) {}

void Creature::initCreature()
{
	creatureColor = Colors::WHITE;
	setCreaturePosition();
}

void Creature::collectCreatureStartingPos(GameBoard& board)
{
	startingPos = board.collectStartingPos(creatureIcon);
}

void Creature::resetCreaturePosition()
{
	//currPos should changed to startingPos
	//NextPos should changed also to currPos
	currPos = startingPos;
	nextPos = currPos;
	creatureDirection = Direction::STAY;
}

void Creature::setCreatureNextPos()
{
	nextPos.setNextPos(creatureDirection, creatureIcon);
}

bool Creature::isCreaturePositionValid(GameBoard& board)
{
	return nextPos.isPositionValid(board, creatureIcon);
}

void Creature::printCreature() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ThePacmanGame::isGameColorized()) { setTextColor(creatureColor); }
	cout << creatureIcon;
}

void Creature::convertCharToIcon(char ch)
{
	switch (ch)
	{
	case '@':
		creatureIcon = Icon::PACMAN;
		break;
	case '$':
		creatureIcon = Icon::GHOST;
		break;
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		creatureIcon = Icon::FRUIT;
		break;
	default:
		break;

	}
}