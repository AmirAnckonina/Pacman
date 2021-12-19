#pragma once
#include <queue>
#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"
#include "SmartStrategy.h"
#include "NormalStrategy.h"

using std::cout;
using std::endl;

class Ghost : public Creature
{
public:
	enum GhLevel { NOVICE = 1, GOOD, BEST };

private:
	int ghostLevel;

public:
	~Ghost() {};
	Ghost(char _ghostIcon = Creature::GHOST, int _ghostLevel = NOVICE);
	void initGhost(GameBoard& board, int level);
	void convertGhostLevelToStrategy();
	int getGhostLevel()const { return ghostLevel; }
};