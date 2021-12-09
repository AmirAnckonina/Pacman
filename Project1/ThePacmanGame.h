#pragma once

#include "Utilities.h"
#include "Menu.h"
#include "Directions.h"
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Position.h"

using std::cout;
using std::endl;

class ThePacmanGame
{

public:
	static const int numOfGhosts = 2;
private:
	static bool gameColorized;
	bool ghostsTurn = false;
	bool playerWon = false;
	char userKey;
	Menu game_menu;
	Colors detailsColor = Colors::WHITE;
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[numOfGhosts];

public:
	ThePacmanGame() {};
	//Preparartions functions
	void startGameSessions();
	void initGame();
	void setGameColors();
	static bool isGameColorized() { return gameColorized; }
	

	//Printing functions
	void printFigures() const;
	void printAllGhosts() const;
	void printCollision() const;
	void printCellRestore() const;
	
	//Game functionalliy 
	void runGame();
	void singlePacmanSession();
	void singleGhostsSession();
	bool checkCollision() const;
	void resetAfterCollision();
	bool GameFinished();

};