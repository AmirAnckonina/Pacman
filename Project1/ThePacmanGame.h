#pragma once
using namespace std;


#include "Utilities.h"
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Position.h"


const int numOfGhosts = 2;

class ThePacmanGame
{
private:
	char userKey = 0;
	bool ghostsTurn = false;//to insure that the ghosts will move slowly than the pacman
	bool playerWon = false;
	bool printColorized = false;
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[numOfGhosts];
	Position printPos /*printPos*/;

public:
	char getUserKey() { return userKey; }
	void initGame();
	void runGame();
	void pauseGame();
	void entryMenu();
	void printMenu();
	void printInstructions();
	bool checkCollision();
	void resetAfterCollision();
	void printFigures();
	void printCellRestore();
	void printLives(); //new func chen build
	bool GameFinished();
	void printResult();
	void singleGhostsSession();
	void singlePacmanSession();
};