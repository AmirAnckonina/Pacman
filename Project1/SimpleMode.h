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
	void resetThePacmanGame();
	virtual void runGame() override;
	virtual void collisionProcedure() override;
	virtual void fruitEatenProcedure() override;
	virtual void singleFruitSession() override;
	virtual void completeGhostSession() override; 
	virtual void completePacmanSession() override;


};