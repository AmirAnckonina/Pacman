#include "ThePacmanGame.h"

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, printing rules or instructions.
void ThePacmanGame::initGame()
{
	entryMenu();
	game_board.initBoard();
	game_board.printBoard();
	printLives();
	pacman.setPacman(); 
	ghost[0].setGhost(40, 9);
	ghost[1].setGhost(40, 15);
}

void ThePacmanGame::entryMenu()
{
	char key = 0;
	
	while (key != '1')
	{
		system("cls");
		cout << "Welcome to Pacman game!" << endl;
		cout << "Press (1) to Start" << endl;
		cout << "Press (8) for Instructions" << endl;
		cout << "press (9) to exit" << endl;

		key = _getch();
		
		if (key == '9')
		{
			cout << endl << "Goodbye" << endl;
			exit(1);
		}

		else if (key == '8')
		{
			printInstructions();
		}

		
		key = _getch();
	}

	system("cls");
	Sleep(100);
}

void ThePacmanGame::printInstructions()
{
	system("cls");

	cout << "Welcome to Pacman game!" << endl;
	cout << "Pac - MAN has 3 life in this game."  << endl;
	cout << "Pac - MAN will gain points by collecting all the breadcrumbs in the maze." << endl;
	cout << "You should avoid any interactions with the ghosts. Otherwise, you will be eaten and lose lives." << endl;
	cout << "To win the game you should eat ALL the breadcrumbs" << endl;
	cout << endl;
	cout << endl;
	cout << "Keys instruction:" << endl;
	cout << "Move UP: press w or W " << endl;
	cout << "Move DOWN: press x or X" << endl;
	cout << "Move LEFT: press a or A" << endl;
	cout << "Move RIGHT: press d or D" << endl;
	cout << "To STAY in your position: press s or S" << endl;
	cout << "Good Luck!" << endl;
	cout << endl;
	cout << "Press ESC to return the main menu." << endl;

	char key = 0; 

	key = _getch();
	while (key != ESC)
		key = _getch();

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
		singleGhostsSession();
		singlePacmanSession();
		printFigures();

		if (key == ESC)
		{
			pauseGame();
			key = currDir; //So pacman will continue as he was before pausing.
		}

		Sleep(75);

	} while (!GameFinished());

	printPos.gotoxy(0, 30);
	printResult();
	//system("cls");
	
}

void ThePacmanGame::singleGhostsSession()
{
	if (ghostsTurn) //move the ghosts
	{
		for (auto& gh : ghost)
		{
			gh.moveGhost(game_board);
			gh.updatePos();
		}

		if (checkCollision())
			resetAfterCollision();
		ghostsTurn = false;//they won't move in the next step/
	}
	else //do not move the ghosts
		ghostsTurn = true;
}

void ThePacmanGame::singlePacmanSession()
{
	pacman.movePacman(game_board);
	pacman.updatePos();

	if (!checkCollision())
		pacman.updateScore(game_board);
	else
		resetAfterCollision();
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

	printPos.gotoxy(20, 26);
	cout << "Game paused, press ESC again to continue";

	key = _getch();

	while (key != ESC)// not ESC, to continue
		key = _getch();

	printPos.gotoxy(20, 26);
	cout << "                                        ";//remove everything that was written
}


bool ThePacmanGame::checkCollision()
{
	int pac_x, gh_x, pac_y, gh_y;
	//Mini loop
	pac_x = pacman.getCurrPos().getXPos();
	pac_y = pacman.getCurrPos().getYPos();

	for (auto gh : ghost)
	{
		gh_x = gh.getCurrPos().getXPos();
		gh_y = gh.getCurrPos().getYPos();
		if (pac_x == gh_x && pac_y == gh_y)
			return true;
	}
	return false;
}
void ThePacmanGame::resetAfterCollision()
{
	printCellRestore();
	pacman.resetPacman();
	pacman.setLivesLeft();
	printLives();
	ghost[0].setGhost(40, 9);//was (40,9)
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
void ThePacmanGame::printLives()
{
	printPos.gotoxy(32, 27);
	cout << "Lives Left: " << pacman.getLivesLeft();
}

bool ThePacmanGame::GameFinished()
{
	if (pacman.getLivesLeft() > 0 && game_board.getBreadcrumbs() != pacman.getScore())
		return false;

	else if (pacman.getLivesLeft() == 0)
		playerWon = false;
	else if (game_board.getBreadcrumbs() == pacman.getScore())
		playerWon = true;

	return true;
}

void ThePacmanGame::printResult()
{
	if (playerWon == true)
		cout << "Congratulations, You WON!" << endl << "your score is: " << pacman.getScore() << endl;
	else
		cout << "GAME OVER Shiback, your final score is: " << pacman.getScore() <<  endl;

	cout << "Thanks for playing" << endl;
}