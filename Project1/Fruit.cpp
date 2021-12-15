#include "Fruit.h"

void Fruit::generateFruitValue()
{
	fruitVal = rand() % 9 + 5;
}

//void Fruit::genrateAppearTime()
//{
//	timeOnBoard = rand() % 20 + 10;
//}
Fruit::Fruit(char _fruitIcon) : Creature(_fruitIcon)
{
}
bool Fruit::isActive()
{
	return currentlyActive;
}
//void Fruit::genrateNotAppearTime()
//{
//	timeOnBoard = rand() % 20 + 10;
//}
void Fruit::genrateLocation(GameBoard& board)
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