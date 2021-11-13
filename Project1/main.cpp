
#include <iostream>
using namespace std;

#include "ThePacmanGame.h"
#include "GameBoard.h" //should be to ThePacmanGame.h

int main()
{
	ThePacmanGame game;
	game.initGame();
	game.runGame();
	return 0;
}