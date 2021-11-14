
#include <iostream>
using namespace std;

#include "ThePacmanGame.h"
#include "GameBoard.h" //should be to ThePacmanGame.h

int main()
{
	bool activate = true;

	while (activate)
	{
		ThePacmanGame game;
		game.initGame();
		if (game.getUserKey() == '9')
			activate = false;
		else
			game.runGame();
	}

	return 0;
}


