#pragma once
#include "Utilities.h"
#include "Position.h"
#include <vector>
#include <queue>

class MoveStrategy
{
public:
	//virtual Direction getNextDir(Position& creatureCurrPos ,GameBoard& board, const Position& pacmanPos) = 0;
	//virtual void moveByStrategy(Creature& creature, GameBoard& board, const Position& pacmanPos) = 0;
	virtual Position getNewPosByStrategy(const Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos,
		Direction& creatureDirection, const char creatureIcon) = 0;
};