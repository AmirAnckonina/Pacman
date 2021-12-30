#pragma once
#include "ThePacmanGame.h"

using std::cout;
using std::endl;

class SimpleMode : public ThePacmanGame
{
public:
	static const int MAXNUMOFGHOSTS = 4;

private:
	Menu game_menu;
	int level;
	bool activate = true;
	bool fruitTurn = false;
	
public:
	virtual void runAllSessions() override;
	virtual void runSingleSession(size_t& totalNumOfScreens) override;
	virtual void runGame() override;
	virtual void singleFruitSession() override;
	void resetThePacmanGame();
	void singlePlayerIteration();
};