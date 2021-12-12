#include "Fruit.h"

void Fruit::generateFruitValue()
{
	fruitVal = rand() % 9 + 5;
}

void Fruit::genrateAppearTime()
{
	appearTime = rand() % 20 + 10;
}
/*Fruit::Fruit(char _fruitIcon):Creature(_fruitIcon)
{
}*/
bool Fruit::isActive()
{
	if (appearTime > 0)
		return true;
	return false;
}
void Fruit::genrateNotAppearTime()
{
	appearTime = rand() % 20 + 10;
}
