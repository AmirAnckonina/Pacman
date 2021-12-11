#include "Creature.h"
#include "ThePacmanGame.h"

//char Creature::creatureIcon = 0;

Creature::Creature(char _creatureIcon) : creatureIcon(_creatureIcon) {}

//Creature::Creature(Position _startingPos, Position _currPos, Position _nextPos, Direction _creatureDirection, Colors _creatureColor, char _creatureIcon)
//	: creatureColor(_creatureColor),
//	startingPos(_startingPos),
//	currPos(_currPos),
//	nextPos(_nextPos),
//	creatureDirection(_creatureDirection)
//{
//	//creatureIcon = convertCharToIcon(_creatureIcon);
//	creatureIcon = _creatureIcon;
//}

void Creature::initCreature(GameBoard& board, char _creatureIcon)
{
	creatureColor = Colors::WHITE;
	//creatureIcon = _creatureIcon;
	collectCreatureStartingPos(board);
	board.setCellInBoard(startingPos, GameBoard::BREADCRUMB);
	resetCreaturePosition();
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

void Creature::setCreatureNextPos(GameBoard& board)
{
	nextPos.setNextPos(creatureDirection, creatureIcon, board);
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

//ostream& operator << (ostream& os, Icon _icon)
//{
//	os << (char)_icon;
//}

//Icon Creature::convertCharToIcon(char ch)
//{
//	switch (ch)
//	{
//	case '@':
//		return PACMAN;
//		break;
//	case '$':
//		return GHOST;
//		break;
//	case '5':
//	case '6':
//	case '7':
//	case '8':
//	case '9':
//		return; //FRUIT;
//		break;
//	default:
//		break;
//
//	}
//}