#include "Creature.h"
#include "ThePacmanGame.h"
#include "SmartStrategy.h"
#include "NormalStrategy.h"

//char Creature::creatureIcon = 0;

Creature::Creature(char _creatureIcon, int _creatureStrategyType, MoveStrategy* _mvStrategy, Colors _creatureColor, Direction _creatureDirection)
	: creatureIcon(_creatureIcon), creatureStrategyType(_creatureStrategyType), mvStrategy(_mvStrategy), creatureColor(_creatureColor), creatureDirection(_creatureDirection) {}

void Creature::initCreature(GameBoard& board, char _creatureIcon)
{
	//creatureIcon = _creatureIcon;
	creatureColor = Colors::WHITE;

	if (creatureStrategyType == DYNAMIC)
	{
		hasIntervalTime = true;
		creatureStrategyType = SMART;
	}

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
		if (hasIntervalTime)
			mvStrategy->setMoveInterval(20);
	}
	else if (creatureStrategyType == NORMAL)
	{
		mvStrategy = new NormalStrategy;
		if (hasIntervalTime)
			mvStrategy->setMoveInterval(15);

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

void Creature::replaceStrategyIfNeeded()
{
	if (hasIntervalTime && mvStrategy->getMoveInterval() <= 0)
	{
		//Cnsider using typeid
		if (creatureStrategyType == SMART)
			creatureStrategyType = NORMAL;
		else if (creatureStrategyType == NORMAL)
			creatureStrategyType = SMART;

		setMoveStrategy();
		return;
	}
	else
		return;
}

void Creature::move(GameBoard& board, const Position& pacmanPos)
{
	replaceStrategyIfNeeded();
	mvStrategy->executeMove(*this, board, pacmanPos);
	//nextPos = mvStrategy->getNewPosByStrategy(currPos, board, pacmanPos, creatureDirection, creatureIcon);
	/*generateRandomDirection(creature);
	creature.setCreatureNextPos(board);

	while (!(creature.isCreaturePositionValid(board)))
	{
		creature.resetAfterInvalidNextPos();
		generateRandomDirection(creature);
		creature.setCreatureNextPos(board);
	}*/

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

	if (hasIntervalTime)
		mvStrategy->setMoveInterval((mvStrategy->getMoveInterval() - 1));
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