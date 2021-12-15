#include "Fruit.h"
#include "ThePacmanGame.h"


void Fruit::printCreature()const
{

	gotoxy(getCurrPos().getXPos(), getCurrPos().getYPos());
	if (ThePacmanGame::isGameColorized())
		setTextColor(getColor());
	cout << fruitVal;

}

void Fruit::initFruit()
{
	setColor(Colors::WHITE);
	currentlyActive = false;
	fruitVal = 5;
	timeOnBoard = 20;
	timeOffBoard = 20;
	setCreatureStrategyType(NORMAL);
	setMoveStrategy();
}

void Fruit::generateFruitValue()
{
	fruitVal = (rand() % 9) + 4;
}

//void Fruit::genrateAppearTime()
//{
//	timeOnBoard = rand() % 20 + 10;
//}
Fruit::Fruit(char _fruitIcon, int _fruitStrategyType) : Creature(_fruitIcon, _fruitStrategyType) {}

//void Fruit::genrateNotAppearTime()
//{
//	timeOnBoard = rand() % 20 + 10;
//}
void Fruit::generateLocation(GameBoard& board)
{
	Position newPos;
	bool isValid = false;

	while (!isValid)
	{
		newPos.setXPos(rand() % board.getLastCol() + board.getFirstCol());
		newPos.setYPos(rand() % board.getLastRow() + board.getFirstRow());
		setNextPos(newPos);

		isValid = isCreaturePositionValid(board);

	}
	updatePos();
}

