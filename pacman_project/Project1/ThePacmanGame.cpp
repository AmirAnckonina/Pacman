#include "ThePacmanGame.h"

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, printing rules or instructions.
void ThePacmanGame::initGame()
{
	game_board.initBoard();
	game_board.printBoard();
	pacman.setPacman(game_board);
}

//Running a game session, according to do-while loop condition
void ThePacmanGame::runGame()
{
	char key = 0;
	int currDir;

	do 
	{
		if (_kbhit())
		{
			key = _getch();
			currDir = pacman.getDirection(key); //A kind of key validation.
			if (currDir != -1)
				pacman.setDirection(currDir);
		}
		//Setting new potential position to pacman
		pacman.setNextPos();
		//Sending to move pacman the next cell content.
		pacman.movePacman(game_board);
		/*ghost[0].moveGhost();
		ghost[1].moveGhost();*/
		//sleep();

		} while(key != 27);//(ESC or Pacman dead or Pacman won)
		//pacman.getScore < 1155 ??? 

		//Add pint blank lines at the end
}

