#include "InputStrategy.h"
#include "Creature.h"

void InputStrategy::executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos)
{
	creature.setCreatureNextPos(board);

	if (!creature.isCreaturePositionValid(board))
	{
		creature.resetAfterInvalidNextPos();
		creature.setDirection(Direction::STAY);
		creature.setCreatureNextPos(board);
	}
}

