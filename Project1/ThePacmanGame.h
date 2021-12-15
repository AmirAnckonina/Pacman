#pragma once

#include "Utilities.h"
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
	GameBoard game_board;
	Pacman pacman;
	//Fruit fruit;
	int level;
	Ghost ghost[MAXNUMOFGHOSTS];
	Fruit fruit;
	int numOfGhosts;
	static bool gameColorized;
	bool ghostsTurn = false;
	bool fruitTurn = false;
	bool playerWon = false;

public:
	//Preparartions functions
	void startGameSessions();
	void initGame();
	void setGameColors();
	static bool isGameColorized() { return gameColorized; }


	//Printing functions
	void printFigures() const;
	void printAllGhosts() const;
	void printCollision() const;
	void cellsRestoreAfterCollision() const;
	void generalCellRestore(const Creature& creature) const;

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