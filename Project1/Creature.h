#pragma once

#include "Utilities.h"
#include "Position.h"
#include "GameBoard.h"
//#include "SmartStrategy.h"
//#include "NormalStrategy.h"

class MoveStrategy;
class SmartStrategy;
class NormalStrategy;

class Creature
{
public:
	enum StrategyType { NONE, NORMAL, DYNAMIC, SMART }; //NOVICE = 1, GOOD, BEST, EXTREME
	static constexpr char PACMAN = '@', GHOST = '$', FRUIT = 'F';

private:
	bool hasIntervalTime = false;
	const char creatureIcon;
	int creatureStrategyType;
	MoveStrategy* mvStrategy;

	Position startingPos, currPos, nextPos;
	Direction creatureDirection;
	Colors creatureColor;

public:
	Creature(char _creatureIcon = 0, int _creatureStrategyType = NONE, MoveStrategy* _mvStrategy = nullptr,
		Colors _creatureColor = Colors::WHITE, Direction _creatureDirection = Direction::STAY);

	virtual void move(GameBoard& board, const Position& pacmanPos = NULL);
	void setMoveStrategy();
	void setCreatureStrategyType(int _creatureStrategyType) { creatureStrategyType = _creatureStrategyType; }
	void replaceStrategyIfNeeded();
	//-------------------------------------------------------------------------------------
	void initCreature(GameBoard& board, char _creatureIcon);
	void updatePos() { currPos = nextPos; }
	void resetNextPos() { nextPos = currPos; }


	//Get-Set Functions
	char getCreatureIcon() { return creatureIcon; }
	void resetCreaturePosition();


	void setStartingPos(Position _startingPos) { startingPos = _startingPos; }
	Position getStartingPos() const { return startingPos; }

	void setCurrPos(Position _currPos) { currPos = _currPos; }
	const Position& getCurrPos() const { return currPos; }

	void setNextPos(Position _nextPos) { nextPos = _nextPos; }
	const Position& getNextPos() const { return nextPos; }

	void setCreatureNextPos(GameBoard& board);

	void setDirection(Direction _creatureDirection) { creatureDirection = _creatureDirection; }
	Direction getDirection() const { return creatureDirection; }

	void setColor(Colors _creatureColor) { creatureColor = _creatureColor; }
	Colors getColor() const { return creatureColor; }

	//void setIcon(char _creatureIcon) { creatureIcon = _creatureIcon; }
	char getIcon() const { return creatureIcon; }

	bool isCreaturePositionValid(GameBoard& board);
	virtual void printCreature() const;

	void collectCreatureStartingPos(GameBoard& board);
	void resetAfterInvalidNextPos();

};
