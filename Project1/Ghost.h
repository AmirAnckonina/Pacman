#pragma once
#include <queue>
#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"
#include "GhRegularStrategy.h"
#include "GhSmartStrategy.h"

using std::queue;

using std::cout;
using std::endl;

class Ghost :public Creature
{
public:
	enum StrategyType {NOVICE, GOOD, BEST, EXTREME};
private:
	GhStrategy *gh_strategy;
public:
	Ghost(char __ghostIcon = Creature::GHOST);
	/*Ghost(Position _ghostStartingPos, Position _ghostCurrPos, Position _ghostNextPos,
		Direction _ghostDirection = Direction::STAY, Colors _ghostColor = Colors::WHITE, char _ghostIcon = Creature::GHOST);*/
	void initGhost(GameBoard& board);
	void moveGhost(GameBoard& board);
	void generateRandomDirection();
	void setStrategy(StrategyType choice);

	void smartGhostMove(GameBoard& board, Position start, Position ghostPos);
};