#include "Creature.h"
#include "ThePacmanGame.h"

//char Creature::creatureIcon = 0;

Creature::Creature(char _creatureIcon, int _creatureStrategyType, MoveStrategy* _mvStrategy, Colors _creatureColor, Direction _creatureDirection)
	: creatureIcon(_creatureIcon), creatureStrategyType(_creatureStrategyType), mvStrategy(_mvStrategy), creatureColor(_creatureColor), creatureDirection(_creatureDirection) {}

void Creature::initCreature(GameBoard& board, char _creatureIcon)
{
	//creatureIcon = _creatureIcon;
	creatureColor = Colors::WHITE;
	setMoveStrategy();
	collectCreatureStartingPos(board);
	board.setCellInBoard(startingPos, GameBoard::BREADCRUMB);
	resetCreaturePosition();
}

void Creature::setMoveStrategy() //set move strategy according to creatureStrategyType
{
	delete mvStrategy;

	if (creatureStrategyType == SMART)
	{
		mvStrategy = new SmartStrategy;
	}
	else if (creatureStrategyType == NORMAL)
	{
		mvStrategy = new NormalStrategy;
	}
	else //creatureStrategyType == NONE
	{
		mvStrategy = nullptr;
	}
}


void Creature::collectCreatureStartingPos(GameBoard& board)
{
	startingPos = board.collectStartingPos(creatureIcon);
}

void Creature::move(GameBoard& board, const Position& pacmanPos)
{
	creatureDirection = mvStrategy->getNextDir(currPos, board, pacmanPos);
	setCreatureNextPos(board);

	while ( !(isCreaturePositionValid(board)) )
	{
		resetAfterInvalidNextPos();
		creatureDirection = mvStrategy->getNextDir(currPos, board, pacmanPos);
		setCreatureNextPos(board);
	}

	//Final Part
	gotoxy(currPos.getXPos(), currPos.getYPos());
	//The ghost printed and we want the print of the cell as it were before.
	if (board.getCellInBoard(currPos) == GameBoard::BREADCRUMB)
	{
		if (ThePacmanGame::isGameColorized())
			setTextColor(board.getBreadcrumbColor());

		cout << GameBoard::BREADCRUMB;
	}
	else
		cout << GameBoard::SPACE;
}

void Creature::resetAfterInvalidNextPos()
{
	nextPos = currPos;	
	if (creatureIcon != GHOST)
		creatureDirection = Direction::STAY;
}

void Creature::resetCreaturePosition()
{
	//currPos should changed to startingPos
	//NextPos should changed also to currPos
	currPos = startingPos;
	nextPos = currPos;
	creatureDirection = Direction::STAY;
}
//???????
void Creature::setCreatureNextPos(GameBoard& board)
{
	nextPos.setNextPos(creatureDirection, creatureIcon, board); //????
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