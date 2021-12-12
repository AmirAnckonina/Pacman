#pragma once
#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"



class Fruit
{
public:
	static constexpr char FRUIT = '5';
private:
	int fruitVal;
	Colors fruitColor = Colors::WHITE;

	Position currPos, nextPos;
	Direction pacmanDirection = Direction::STAY;
	int appearTime;
	int notAppearTime;



public:
	Fruit(char _fruitIcon = Creature::FRUIT);

	void generateFruitValue();
	void genrateAppearTime();
	void genrateNotAppearTime();

	//Get-Set Functions
	int getAppearTime() { return appearTime; };
	int getNotAppearTime() { return notAppearTime; };
	bool isActive();


	//void getFruitDir();
	//void setFruitPos();
	//void setFruitColor(Colors color) { fruitColor = color; }
	//Colors getFruitColor() const { return fruitColor; }
	//Position getCurrPos() const { return currPos; }



};