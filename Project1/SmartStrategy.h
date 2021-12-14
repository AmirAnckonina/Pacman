#pragma once
#include "MoveStrategy.h"


using std::queue;

class SmartStrategy : public MoveStrategy
{
private:
	int smartMoveInterval = 0;
public:
	//virtual int getMoveInterval() const override { return smartMoveInterval; }
	//void convertNeighborsToDirection(Direction& resDir, int _addedY, int _addedX);
	//virtual void executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos) override;
	virtual Position getNewPosByStrategy(const Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos,
		Direction& creatureDirection, const char creatureIcon) override;
	bool isNeighborCellIsGhost(const Position& creatureCurrPos, int neighborY, int neighborX);
	//void setNextPosBFS(GameBoard& board, Creature& creature, const Position& pacmanPos);
	void setNextPosBFS(GameBoard& board, const Position& creatureCurrPos, const Position& pacmanPos, Position& newNextPos);
	//bool cellShouldEnterQueue(GameBoard& board, int neighborY, int neighborX);
	bool cellShouldEnterQueue(GameBoard& board, Position& adjCoord);
};