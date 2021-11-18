
#include <iostream>
using std::cout;
using std::endl;


#include "ThePacmanGame.h"
#include "GameBoard.h" //should be to ThePacmanGame.h

int main()
{
	bool activate = true;
	ThePacmanGame game;

	while (activate)
	{
		game.entryMenu();
		if (game.getUserKey() == EXIT)
			activate = false;
		else
		{
			game.initGame();
			game.runGame();
		}
	}

	cout << endl << "Goodbye" << endl;
	return 0;
}


