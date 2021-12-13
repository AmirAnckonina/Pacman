#pragma once
#include "Utilities.h"
#include "Position.h"
#include <vector>

class MoveStrategy
{
public:
	virtual Direction getNextDir(Position& creatureCurrPos ,GameBoard& board, const Position& pacmanPos) = 0;
};