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
	void runAllSessions();
	virtual void runSingleSession(size_t& totalNumOfScreens);
	virtual void initGame();
	void setGameColors();
	static bool isGameColorized() { return gameColorized; }
	void printAfterInit();

	//Printing functions
	void printFigures() const;
	void printAllGhosts() const;
	void printCollision() const;
	void cellsRestoreAfterCollision() const;
	void generalCellRestore(const Creature& creature) const;
	void resetThePacmanGame();

	//Game functionalliy 
	virtual void runGame();
	virtual void singlePacmanSession();
	void completePacmanSession();

	void singleFruitSession();
	virtual void singleGhostsSession();
	bool checkCollision() const;
	bool isFruitEatenByPacman();
	bool isFruitEatenByGhost();
	void fruitEatenProcedure();

	virtual void resetAfterCollision();
	bool GameFinished();
	void runAllGameBoards(bool& activate);
	void afterCollisionPrinting();

};