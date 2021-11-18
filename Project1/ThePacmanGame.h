#pragma once

#include "Utilities.h"
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Position.h"

using std::cout;
using std::endl;

const int numOfGhosts = 2;

class ThePacmanGame
{
private:

	char userKey;
	bool ghostsTurn = false;
	bool playerWon = false;
	bool gameColorized = false;
  gameColors detailsColor = gameColors::WHITE
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[numOfGhosts];

public:

	void printFigures();
	char getUserKey() const { return userKey; }
	void initGame();
	void runGame();
	void pauseGame();
	void entryMenu();
	bool userChoosedToStart();
	void setGameColors();
	void printMenu();
	void printAllGhosts() const;
	void printInstructions();
	bool checkCollision();
	void resetAfterCollision();
	void printCellRestore();
	void printLives(); 
	bool GameFinished();
	void printResult();
	void singleGhostsSession();
	void singlePacmanSession();
  
};