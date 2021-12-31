#pragma once

#include "Utilities.h"
#include "Position.h"
#include "GameBoard.h"

class MoveStrategy;
class SmartStrategy;
class NormalStrategy;
class InputStrategy;

class Creature
{
public:
	enum StrategyType { NONE, NORMAL, DYNAMIC, SMART, INPUT }; 
	static constexpr char PACMAN = '@', GHOST = '$', FRUIT = 'F';

private:
	bool hasIntervalTime = false;
	bool nextPosIsValid = false;
	const char creatureIcon;
	int creatureStrategyType;
	MoveStrategy* mvStrategy;
	Position startingPos, currPos, nextPos, prevPos;
	Direction creatureDirection;
	Colors creatureColor;

public:
	//C'tor - D'tor
	Creature(char _creatureIcon = 0, int _creatureStrategyType = NONE, MoveStrategy* _mvStrategy = nullptr,
		Colors _creatureColor = Colors::WHITE, Direction _creatureDirection = Direction::STAY);
	virtual ~Creature();
	virtual void move(GameBoard& board, const Position& pacmanPos = NULL);
	virtual void afterMoveProcedure(GameBoard& board);
	//Strategy
	void setMoveStrategy();
	void setCreatureStrategyType(int _creatureStrategyType) { creatureStrategyType = _creatureStrategyType; }
	void replaceStrategyIfNeeded();

	void initCreature(GameBoard& board, char _creatureIcon, int _creatureStrategyType = NONE);
	void resetNextPos() { nextPos = currPos; }
	void updatePos() { currPos = nextPos; }
	void resetCreaturePosition();
	bool isCreaturePositionValid(GameBoard& board);
	void updateIntervalInStrategyIfNeeded();


	//Get-Set Functions
	virtual void printCreature() const;
	bool getNextPosIsValid() { return nextPosIsValid; }
	void setNextPosIsValid(bool _isValid) { nextPosIsValid = _isValid; }
	void collectCreatureStartingPos(GameBoard& board);
	void resetAfterInvalidNextPos();
	char getCreatureIcon() { return creatureIcon; }
	void setStartingPos(Position _startingPos) { startingPos = _startingPos; }
	Position getStartingPos() const { return startingPos; }
	const Position& getPrevPos() const { return prevPos; }
	void updatePrevPos() { prevPos = currPos; }
	void setCurrPos(int x, int y);
	void setCurrPos(Position _currPos) { currPos = _currPos; }
	const Position& getCurrPos() const { return currPos; }
	void setNextPos(Position _nextPos) { nextPos = _nextPos; }
	const Position& getNextPos() const { return nextPos; }
	void setCreatureNextPos(GameBoard& board);
	void setDirection(Direction _creatureDirection) { creatureDirection = _creatureDirection; }
	Direction getDirection() const { return creatureDirection; }
	void setColor(Colors _creatureColor) { creatureColor = _creatureColor; }
	Colors getColor() const { return creatureColor; }
	char getIcon() const { return creatureIcon; }

};
