#include "Ghost.h"
#include "ThePacmanGame.h"
#include "Menu.h"

Ghost::Ghost(char _ghostIcon, int _ghostLevel) : Creature(_ghostIcon), ghostLevel(_ghostLevel) {}

void Ghost::initGhost(GameBoard& board, int level)
{
	ghostLevel = level;
	convertGhostLevelToStrategy();
	setCreatureStrategyType(ghostLevel);
	initCreature(board, Creature::GHOST);
}

void Ghost::convertGhostLevelToStrategy()
{
	switch (ghostLevel)
	{
	case BEST:
		setCreatureStrategyType(SMART);
		break;
	case GOOD:
		setCreatureStrategyType(DYNAMIC);
		break;
	case NOVICE:
		setCreatureStrategyType(NORMAL);
		break;
	default:
		break;
	}
}

