#include "NormalStrategy.h"
#include "Creature.h"

void NormalStrategy::executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos)
{
	/*generateRandomDirection(creature);
	creature.setCreatureNextPos(board);*/
	bool isValid = false;
	int maxTriesOfGettingValidPos = 30;

	while (!isValid) //(creature.isCreaturePositionValid(board)))
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
		//setDirection(Direction::UP);
		creature.setDirection(Direction::UP);
		break;
	case 2:
		//setDirection(Direction::DOWN);
		creature.setDirection(Direction::DOWN);
		break;
	case 3:
		//setDirection(Direction::LEFT);
		creature.setDirection(Direction::LEFT);
		break;
	case 4:
		//setDirection(Direction::RIGHT);
		creature.setDirection(Direction::RIGHT);
		break;
	default:
		break;
	}
}


//Position NormalStrategy::getNewPosByStrategy(const Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos, Direction& creatureDirection, const char creatureIcon)
//{
//	Position newNextPos;
//	bool isValid = false;
//	
//	while (!isValid)
//	{
//		newNextPos = creatureCurrPos;
//		generateRandomDirection(creatureDirection);
//		newNextPos.setNextPos(creatureDirection, creatureIcon, board);
//		isValid = newNextPos.isPositionValid(board, creatureIcon);
//	}
//	return newNextPos;
//}
//
//void NormalStrategy::generateRandomDirection(Direction& creatureDirection)
//{
//	int dirInd = rand() % 4 + 1;
//	switch (dirInd)
//	{
//	case 1:
//		//setDirection(Direction::UP);
//		creatureDirection = (Direction::UP);
//		break;
//	case 2:
//		//setDirection(Direction::DOWN);
//		creatureDirection = (Direction::DOWN);
//		break;
//	case 3:
//		/*setDirection(Direction::LEFT);*/
//		creatureDirection = (Direction::LEFT);
//		break;
//	case 4:
//		//setDirection(Direction::RIGHT);
//		creatureDirection = (Direction::RIGHT);
//		break;
//	default:
//		break;
//	}
//}

