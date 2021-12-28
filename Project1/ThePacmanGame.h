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
	void afterPacmanMoveProcedure();
	void singleFruitSession();
	void singleGhostsSession();
	bool checkCollision() const;
	bool isFruitEatenByPacman();
	bool isFruitEatenByGhost();
	void fruitEatenProcedure();

	void resetAfterCollision();
	bool GameFinished();
	void runAllGameBoards(bool& activate);
	void afterCollisionPrinting();

};