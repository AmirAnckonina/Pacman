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
	gameColors detailsColor = gameColors::WHITE;
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[numOfGhosts];

public:
	void initGame();
	void entryMenu();
	void printInstructions();
	void setGameColors();
	char getUserKey() const { return userKey; }
	bool userChoosedToStart() const;
	void printMenu() const;
	void printLives() const; 
	void printGameName() const;
	void printRSG() const;

	void runGame();
	void singlePacmanSession();
	void singleGhostsSession();
	void resetAfterCollision();
	bool GameFinished();
	void pauseGame() const;
	void printFigures() const;
	void printAllGhosts() const;
	bool checkCollision() const;
	void printCollision() const;
	void printCellRestore() const;
	void printResult() const;
};