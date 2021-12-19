#include "NormalStrategy.h"
#include "Creature.h"

void NormalStrategy::executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos)
{
	bool isValid = false;
	int maxTriesOfGettingValidPos = 30;

	while (!isValid)
	{
		if (--maxTriesOfGettingValidPos > 0)
		{
			creature.resetAfterInvalidNextPos();
			generateRandomDirection(creature);
			creature.setCreatureNextPos(board);
			isValid = creature.isCreaturePositionValid(board);
		}
		else
		{
			creature.setDirection(Direction::STAY);
			creature.resetAfterInvalidNextPos();
			creature.setCreatureNextPos(board);
			isValid = true;
		}
	}
}

void NormalStrategy::generateRandomDirection(Creature& creature)
{
	int dirInd = rand() % 4 + 1;
	switch (dirInd)
	{
	case 1:
		creature.setDirection(Direction::UP);
		break;
	case 2:
		creature.setDirection(Direction::DOWN);
		break;
	case 3:
		creature.setDirection(Direction::LEFT);
		break;
	case 4:
		creature.setDirection(Direction::RIGHT);
		break;
	default:
		break;
	}
}
