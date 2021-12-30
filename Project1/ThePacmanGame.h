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
	Menu game_menu;
	GameShell game_shell;
	GameBoard game_board;
	Pacman pacman;
	int level;
	Ghost ghost[MAXNUMOFGHOSTS];
	Fruit fruit;
	int numOfGhosts;
	static bool gameColorized;
	bool activate = true;
	bool fruitTurn = false;
	bool playerWon = false;


public:

	//Preparartions functions
	virtual void runAllSessions() = 0;
	virtual void runSingleSession(size_t& totalNumOfScreens) = 0;
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
	virtual void runGame() = 0;
	void singlePacmanSession() ;
	virtual void completePacmanSession();
	void singleGhostsSession();
	virtual void completeGhostsSession();
	void updateScoreAndBoardAfterPacman();
	virtual void singleFruitSession() = 0;
	virtual void fruitEatenProcedure(); 
	void singleCreaturesIteration();
	void afterRunGameProcedure();
	bool checkCollision() const;
	bool isFruitEatenByPacman();
	bool isFruitEatenByGhost();
	void collisionProcedure();
	bool GameFinished();
	//void runAllGameBoards(bool& activate);
	
	

};