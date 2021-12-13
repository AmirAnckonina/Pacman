#pragma once
#include <queue>
#include "MoveStrategy.h"

using std::queue;

class SmartStrategy : public MoveStrategy
{
private:
	int smartMoveInterval = 0;
public:
	//virtual int getMoveInterval() const override { return smartMoveInterval; }
	void convertNeighborsToDirection(Direction& resDir, int _addedY, int _addedX);
	bool isNeighborCellIsGhost(Position& creatureCurrPos, int neighborY, int neighborX);
	virtual Direction getNextDir(Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos) override;
};