#pragma once
using namespace std;

#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"

class ThePacmanGame
{

private:
	enum { ESC = 27 };
	GameBoard game_board;
	Pacman pacman;
	//Ghost ghost[2];


public:
	void initGame();
	void runGame();
};
