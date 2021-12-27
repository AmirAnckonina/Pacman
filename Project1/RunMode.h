#pragma once

#include "ThePacmanGame.h"

class RunMode
{
private:
	//ModeManager mode; //get
	RunMode* run_mode;
	Menu game_menu;
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[MAXNUMOFGHOSTS];
	Fruit fruit;
	int numOfGhosts;
	int level;
	static bool gameColorized;
	bool activate = true;
	bool fruitTurn = false;
	bool playerWon = false;

public:
	//Preparartions functions
	void runAllSessions();
	void runSingleSession(size_t& totalNumOfScreens);
	void initGame();
	void setGameColors();
	static bool isGameColorized() { return gameColorized; }

	//Printing functions
	void printFigures() const;
	void printAllGhosts() const;
	void printCollision() const;
	void cellsRestoreAfterCollision() const;
	void generalCellRestore(const Creature& creature) const;
	void resetThePacmanGame();

	//Game functionalliy 
	void runGame();
	void singlePacmanSession();
	void singleFruitSession();
	void singleGhostsSession();
	bool checkCollision() const;
	bool isFruitEatenByPacman();
	bool isFruitEatenByGhost();
	void fruitEatenProcedure();
	void resetAfterCollision();
	bool GameFinished();
	void runAllGameBoards(bool& activate);

};