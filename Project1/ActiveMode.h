#pragma once

#include "RunMode.h"

class ActiveMode
{
private:
	ofstream stepsFile, resultFile;
	bool fruitTurn = false;
	int level;
	bool activate = true;
	Menu game_menu;

public:
	void openFilesForWriting();
};