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
	void generalCellRestore(const Creature& creature) const;
	

	//Game functionalliy 
	virtual void runGame() = 0;
	void singlePacmanSession() ;
	virtual void completePacmanSession() = 0;
	virtual void singleFruitSession() = 0;
	virtual void singleGhostsSession();
	virtual void completeGhostSession() = 0 ;
	void afterGhostMove();

	bool checkCollision() const;

	bool isFruitEatenByPacman();
	bool isFruitEatenByGhost();
	virtual void fruitEatenProcedure() = 0;

	virtual void collisionProcedure();
	bool GameFinished();
	void runAllGameBoards(bool& activate);
	void afterCollisionPrinting();

};