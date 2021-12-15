#pragma once
#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"



class Fruit : public Creature
{

private:
	int fruitVal;
	//bool isFruitActive = true;
	bool currentlyActive = true;
	//Colors fruitColor = Colors::WHITE;
	//Direction pacmanDirection = Direction::STAY;
	int timeOnBoard = 20;
	int timeNotOnBoard = 20;



public:
	Fruit(char _fruitIcon = Creature::FRUIT);

	void generateFruitValue();
	//void genrateAppearTime();
	//void genrateNotAppearTime();
	void genrateLocation(GameBoard& board);

	//Get-Set Functions
	int getTimeOnBoard() { return timeOnBoard; };
	int getTimeNotOnBoard() { return timeNotOnBoard; };
	int getFruitVal() { return fruitVal; }
	//bool isActivity() { return currentlyActive; }
	int disableActivity() { currentlyActive = false; timeNotOnBoard = 20; }
	int setActivity() { currentlyActive = true; timeOnBoard = 20; }
	void ReduceTimeOnBoard() { timeOnBoard--; }
	void ReduceTimeNotOnBoard() { timeNotOnBoard--; }
	bool isActive();


	//void getFruitDir();
	//void setFruitPos();
	//void setFruitColor(Colors color) { fruitColor = color; }
	//Colors getFruitColor() const { return fruitColor; }
	//Position getCurrPos() const { return currPos; }



};