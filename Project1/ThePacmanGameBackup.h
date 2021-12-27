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
	//ModeManager mode; //get
	Menu game_menu;
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
	ofstream resultFile;
	ofstream stepsFile;


public:
	//Preparartions functions
	void runAllSessions();
	void runSingleSession(size_t& totalNumOfScreens);
	void initGame();
	void setGameColors();
	static bool isGameColorized() { return gameColorized; }
	void setGameColorized(bool isColorized) { gameColorized = isColorized; }

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

	GameBoard& getGameBoard() { return game_board; }
	bool isActive() { return activate; }
	bool setActivation(bool _activate) { activate = _activate; }
	Menu& getMenu() { return game_menu; }

	void writeMovesToFile();
	void writePacmanStepToFile();
	void writeGhostStepToFile();
	void writeFruitStepToFile();

};