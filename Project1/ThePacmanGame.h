#pragma once
//using namespace std;


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
	bool ghostsTurn = false;//to insure that the ghosts will move slowly than the pacman
	bool playerWon = false;
	bool gameColorized = false;
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
	void setGameColors();
	void printMenu();
	void printInstructions();
	bool checkCollision();
	void resetAfterCollision();
	void printCellRestore();
	void printLives(); //new func chen build
	bool GameFinished();
	void printResult();
	void singleGhostsSession();
	void singlePacmanSession();
};