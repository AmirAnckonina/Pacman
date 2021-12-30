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
	bool fruitTurn = false;

protected:
	bool activate = true;
public:
	virtual void run() override;

	
	virtual void runAllSessions() override;
	virtual void runSingleScreensSession() override;
	void preparations();
	void presentMenu();
	void initSingleScreen();
	virtual void runSingleScreen();
	void firstBoardProcedure();
	void handleQuit();
	void goodBye();
	void handleSetGameColorized();
	virtual void runGame() override;
	virtual void singleFruitSession() override;
	void resetThePacmanGame();
	void singlePlayerIteration();
};