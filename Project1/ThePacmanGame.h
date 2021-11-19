#pragma once

#include "Utilities.h"
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
	static constexpr char START = '1', STARTCOLORIZED = '2', INSTRUCTIONS = '8', EXIT = '9', ESC = 27;
	char userKey;
	bool ghostsTurn = false;
	bool playerWon = false;
	Colors detailsColor = Colors::WHITE;
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[numOfGhosts];

public:
	void startGameSessions();
	void initGame();
	void entryMenu();
	static bool isGameColorized() { return gameColorized; }
	void printInstructions();
	void setGameColors();
	char getUserKey() const { return userKey; }
	bool userChoosedToStart() const;
	void printMenu() const;
	void printLives() const; 
	void printGameName() const;
	void printRSG() const;
	void printPacmanAllAround() const;
	void printGhostsAllAround() const;
	void clearRectangle() const;

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