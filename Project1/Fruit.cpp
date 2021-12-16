#include "Fruit.h"
#include "ThePacmanGame.h"

Fruit::Fruit(char _fruitIcon, int _fruitStrategyType) : Creature(_fruitIcon, _fruitStrategyType) {}

void Fruit::printCreature()const
{
	if (currentlyActive)
	{
		gotoxy(getCurrPos().getXPos(), getCurrPos().getYPos());
		if (ThePacmanGame::isGameColorized())
			setTextColor(getColor());
		cout << fruitVal;
	}
}

void Fruit::initFruit()
{
	setColor(Colors::WHITE);
	currentlyActive = false;
	fruitVal = 5;
	timeOnBoard = 40;
	timeOffBoard = 40;
	setCreatureStrategyType(NORMAL);
	setMoveStrategy();
	resetNextPos();
}

void Fruit::generateFruitValue()
{
	fruitVal = (rand() % 4) + 5;
}

void Fruit::generateLocation(GameBoard& board)
{
	Position newPos;
	bool isValid = false;

	while (!isValid)
	{
		newPos.setXPos((rand() % board.getLastCol()) + board.getFirstCol());
		newPos.setYPos((rand() % board.getLastRow()) + board.getFirstRow());
		setNextPos(newPos);
		isValid = isCreaturePositionValid(board);
	}
	updatePos();
}

void Fruit::disableActivity()
{
	currentlyActive = false; 
	timeOffBoard = 40;
}

