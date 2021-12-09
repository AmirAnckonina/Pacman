#pragma once
#include <queue>
#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"

using std::queue;

using std::cout;
using std::endl;

class Ghost :public Creature
{

public:
	Ghost() {};
	Ghost(Position _ghostStartingPos, Position _ghostCurrPos, Position _ghostNextPos,
		Direction _ghostDirection = Direction::STAY, Colors _ghostColor = Colors::WHITE, char _ghostIcon = '$');
	void initGhost(GameBoard& board);
	void moveGhost(GameBoard& board);
	void generateRandomDirection();
	//void smartGhostMove();
};