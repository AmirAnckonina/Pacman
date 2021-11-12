#include "ThePacmanGame.h"

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, printing rules or instructions.
void ThePacmanGame::initGame()
{
	game_board.initBoard();
	game_board.printBoard();
	pacman.setPacman();
	//new code 
	ghost[0].setGhost(40, 9);
	ghost[1].setGhost(40, 15);

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
		//changed from here and below

		if (!holdTheGhosts)//move the ghosts
		{
			for (auto& gh : ghost)
			{
				gh.moveGhost(game_board);
				gh.updatePos();	
			}
			checkCollision();
			holdTheGhosts = true;//they will move in the next step/
		}
		else //do not move the ghosts
			holdTheGhosts = false;

		//Sending to move pacman the next cell content.
		pacman.movePacman(game_board);
		pacman.updatePos();

		if (!checkCollision())
			pacman.updateScore(game_board);
		else
			resetAfterCollision();

		printFigures();
		
		if (key == 27)
		{
			pauseGame();
			key = currDir;
		}

		Sleep(300);

	} while (true);//(ESC or Pacman dead or Pacman won)
	//pacman.getScore < 1155 ??? 

	pausePos.gotoxy(0, 30);
}

void ThePacmanGame::printFigures()
{
	pacman.printPacman();
	for (auto& gh : ghost)
		gh.printGhost();
}

void ThePacmanGame::pauseGame()
{
	char key;

	pausePos.gotoxy(20, 26);
	cout << "Game paused, press ESC again to continue";

	key = _getch();

	while (key != 27)// not ESC, to continue
		key = _getch();

	pausePos.gotoxy(20, 26);
	cout << "                                        ";//remove everything that was written
}


bool ThePacmanGame::checkCollision()
{
	int pac_x, gh_x, pac_y, gh_y;
	//Mini loop
	for (auto gh : ghost)
	{
		pac_x = pacman.getCurrPos().getXPos();
		pac_y = pacman.getCurrPos().getYPos();
		gh_x = gh.getCurrPos().getXPos();
		gh_y = gh.getCurrPos().getYPos();
		if (pac_x == gh_x && pac_y == gh_y)
		{
			cout << "Collision!!!";
			return true;
		}
	}
	return false;
}
void ThePacmanGame::resetAfterCollision()
{
		printCellRestore();
		pacman.resetPacman();
		pacman.setLivesLeft();
		ghost[0].setGhost(40, 9);
		ghost[1].setGhost(40, 15);
}

void ThePacmanGame::printCellRestore()
{ 
	char cell;
	int x, y;

	x = pacman.getCurrPos().getXPos();
	y = pacman.getCurrPos().getYPos();
	cell = game_board.getCellInBoard(x, y);
	pacman.getCurrPos().gotoxy(x, y);
	cout << cell;

	for (auto& gh : ghost)
	{
		x = gh.getCurrPos().getXPos();
		y = gh.getCurrPos().getYPos();
		cell = game_board.getCellInBoard(x, y);
		gh.getCurrPos().gotoxy(x, y);
		cout << cell;
	}
	
}