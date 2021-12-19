#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"

class Fruit : public Creature
{

private:
	int fruitVal = 5;
	bool currentlyActive = false;
	int timeOnBoard = 20;
	int timeOffBoard = 20;

public:
	Fruit(char _fruitIcon = Creature::FRUIT, int _fruitStrategyType = NORMAL);
	~Fruit() {};

	void generateFruitValue();
	void generateLocation(GameBoard& board);

	//Get-Set Functions
	int getTimeOnBoard() const { return timeOnBoard; };
	int getTimeOffBoard() const { return timeOffBoard; };
	int getFruitVal() const { return fruitVal; }
	void disableActivity();
	void enableActivity() { currentlyActive = true; timeOnBoard = 40; }
	void ReduceTimeOnBoard() { timeOnBoard--; }
	void ReduceTimeOffBoard() { timeOffBoard--; }
	bool isActive() const { return currentlyActive; }
	virtual void printCreature()const override;
	void initFruit();

};