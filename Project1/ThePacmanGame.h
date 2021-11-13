#pragma once
using namespace std;

#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"

const int numOfGhosts = 2;

class ThePacmanGame
{

private:
	bool holdTheGhosts = true;//to insure that the ghosts will move slowly than the pacman
	enum { ESC = 27 };
	GameBoard game_board;
	Pacman pacman;
	Ghost ghost[numOfGhosts];
	Position pausePos /*printPos*/;

public:
	void initGame();
	void runGame();
	void pauseGame();
	bool checkCollision();
	void resetAfterCollision();
	void printFigures();
	void printCellRestore();
	//void printLives();//new func chen build
};