#pragma once
#include "MoveStrategy.h"

class Creature;

class SmartStrategy : public MoveStrategy
{
private:
	int smartMoveInterval = 0;
public:
	~SmartStrategy() override {};
	virtual void setMoveInterval(int _mvInterval) override { smartMoveInterval = _mvInterval; }
	virtual int getMoveInterval() const override { return smartMoveInterval; }
	virtual void executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos) override;
	void setNextPosBFS(GameBoard& board, Creature& creature, const Position& pacmanPos);
	bool cellShouldEnterQueue(GameBoard& board, Position& adjCoord);
};