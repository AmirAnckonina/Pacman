#pragma once
#include "MoveStrategy.h"

class Creature;

class InputStrategy : public MoveStrategy
{
private:
	int inputMoveInterval = 0;
public:
	~InputStrategy()override {};
	virtual void setMoveInterval(int _mvInterval) override { inputMoveInterval = _mvInterval; }
	virtual int getMoveInterval() const override { return inputMoveInterval; }
	virtual void executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos) override;
};
