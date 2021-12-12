#pragma once
#include "GhStrategy.h"

class GhRegularStrategy : public GhStrategy
{

	void Ghost::generateRandomDirection(Position& ghostPos)
	{
		int dirInd = rand() % 4 + 1;
		switch (dirInd)
		{
		case 1:
			setDirection(Direction::UP);
			break;
		case 2:
			setDirection(Direction::DOWN);
			break;
		case 3:
			setDirection(Direction::LEFT);
			break;
		case 4:
			setDirection(Direction::RIGHT);
			break;
		default:
			break;
		}

		ghostPos.setCreaturePos()

	}
};