#include "NormalStrategy.h"

Direction NormalStrategy::getNextDir(Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos)
{
	Direction resDir;
	generateRandomDirection(resDir);
	return resDir;
}

void NormalStrategy::generateRandomDirection(Direction& resDir)
{
	int dirInd = rand() % 4 + 1;
	switch (dirInd)
	{
	case 1:
		//setDirection(Direction::UP);
		resDir = Direction::UP;
		break;
	case 2:
		//setDirection(Direction::DOWN);
		resDir = Direction::DOWN;
		break;
	case 3:
		/*setDirection(Direction::LEFT);*/
		resDir = Direction::LEFT;
		break;
	case 4:
		//setDirection(Direction::RIGHT);
		resDir = Direction::RIGHT;
		break;
	default:
		break;
	}
}

