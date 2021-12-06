#pragma once
#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "
.h"


class Fruit
{
public:
	static constexpr char FRUIT = '5';
private:
	int fruitVal;
	Colors fruitColor = Colors::WHITE;
	Position currPos, nextPos;
	Direction pacmanDirection = Direction::STAY;


public:
	void generateFruitValue();

	//Get-Set Functions
	void getFruitDir();
	void setFruitPos();
	void setFruitColor(Colors color) { fruitColor = color; }
	Colors getFruitColor() const { return fruitColor; }
	Position getCurrPos() const { return currPos; }

};