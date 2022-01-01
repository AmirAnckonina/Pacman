#pragma once

#include "Utilities.h"
#include "GameShell.h"
#include "Menu.h"
#include "Directions.h"
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Position.h"
#include "Fruit.h"

using std::cout;
using std::endl;

class ThePacmanGame
{

public:
	static const int MAXNUMOFGHOSTS = 4;

protected:
	int j = 0;//manage the turns of the ghosts(even/odd)
	GameShell game_shell;
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[MAXNUMOFGHOSTS];
	Fruit fruit;
	int currScreenInd = 0;
	size_t totalNumOfScreens;
	bool pacmanDied = false; //Pacman Direction: 
	int numOfGhosts;
	static bool gameColorized;
	bool activate = true;
	bool playerWon = false;
	bool fruitTurn = false;
	bool collisionInCurrStepIndicator = false;


public:

	//Preparartions functions
	virtual void run() = 0;
	virtual void runAllSessions() = 0;
	virtual void runSingleScreensSession()= 0;
	virtual void runGame() = 0;
	virtual void singleFruitSession() = 0;
	virtual void initSingleScreen(int _level = 0);
	virtual void runSingleScreen();
	
	void loadScreens();
	void goodBye();
	
	void initGame(int ghostLevel = 0);
	void setGameColors();
	static bool isGameColorized() { return gameColorized; }
	void printAfterInit();

	//Printing functions
	void printFigures() const;
	void printAllGhosts() const;
	void printCollision() const;
	void cellsRestoreAfterCollision() const;
	void afterCollisionPrinting();
	void generalCellRestore(const Creature& creature) const;
	void afterGhostsMove();
	
	//Game functionalliy 
	
	void singlePacmanSession() ;
	virtual void completePacmanSession();
	void singleGhostsSession();
	virtual void completeGhostsSession();
	void updateScoreAndBoardAfterPacman();
	virtual void fruitEatenProcedure(); 
	void singleCreaturesIteration();
	void afterRunGameProcedure();
	bool checkCollision() const;
	bool isFruitEatenByPacman();
	bool isFruitEatenByGhost();
	void collisionProcedure();
	bool GameFinished();

};