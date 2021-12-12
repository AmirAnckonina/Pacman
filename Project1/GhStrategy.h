#pragma once
#include "Position.h"

class GhStrategy
{
public:
	virtual void setGhostNextPos(GameBoard& board, const Position& pacmanPos, Position& ghostPos) = 0;

};