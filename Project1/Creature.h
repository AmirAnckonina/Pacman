#pragma once

#include "Utilities.h"
#include "Position.h"
#include "GameBoard.h"

//enum Icon {PACMAN = '@', GHOST = '$'};

class Creature
{
public:
	static constexpr char PACMAN = '@', GHOST = '$';

private:
	//Icon creatureIcon;
	char creatureIcon;
	Position startingPos ,currPos, nextPos;
	Direction creatureDirection = Direction::STAY;
	Colors creatureColor = Colors::WHITE;

public:
	Creature(char _creatureIcon = 0);
	/*Creature(Position _startingPos, Position _currPos, Position _nextPos,
		Direction _creatureDirection, Colors _creatureColor, char _creatureIcon);*/

	//void moveCreature(GameBoard& board);
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
	void setCreatureNextPos(GameBoard& board);
	const Position& getNextPos() const { return nextPos; }

	void setDirection(Direction _creatureDirection) { creatureDirection = _creatureDirection; }
	Direction getDirection() const { return creatureDirection; }

	void setColor(Colors _creatureColor) { creatureColor = _creatureColor; }
	Colors getColor() const { return creatureColor; }

	void setIcon(char _creatureIcon) { creatureIcon = _creatureIcon; }
	char getIcon() const { return creatureIcon; }

	bool isCreaturePositionValid(GameBoard& board);
	void printCreature() const ;

	void collectCreatureStartingPos(GameBoard& board);

	//Icon convertCharToIcon(char ch);
};
