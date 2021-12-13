#pragma once
#include "MoveStrategy.h"

class NormalStrategy : public MoveStrategy
{
private:
	int normalMoveInterval = 0;
public:
	//virtual int getMoveInterval() const override { return normalMoveInterval; }
	virtual Direction getNextDir(Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos) override;
	void generateRandomDirection(Direction& resDir);
};