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
	Position legendAreaPos;

public:
	//Preparartions functions
	void startGameSessions();
	void initGame();
	void setGameColors();
	static bool isGameColorized() { return gameColorized; }
	

	//Printing functions
	void printLives() const;
	void printGameName() const;
	void printRSG() const;
	void printPacmanAllAround() const;
	void printGhostsAllAround() const;
	void clearLegendArea() const;
	void singlePrintScore() const;
	void printFigures() const;
	void printAllGhosts() const;
	void printCollision() const;
	void printCellRestore() const;
	void printResult() const;

	//Game functionalliy 
	void runGame();
	void pauseGame() const;
	void singlePacmanSession();
	void singleGhostsSession();
	bool checkCollision() const;
	void resetAfterCollision();
	bool GameFinished();


};