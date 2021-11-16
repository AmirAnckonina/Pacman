#include "ThePacmanGame.h"

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, printing rules or instructions.
void ThePacmanGame::initGame()
{
	hideCursor();
	entryMenu();
	if (userKey != EXIT)
	{
		game_board.initBoard();
		game_board.printBoard();
		printLives();
		pacman.setPacman();
		ghost[0].setGhost(40, 9);
		ghost[1].setGhost(40, 15);
	}
	else
		cout << endl << "Goodbye" << endl;
}

void ThePacmanGame::entryMenu()
{
	cout << "Press any key to enter the game menu..." << endl;
	userKey = _getch();
	userKey = 0;

	while (userKey != START && userKey != STARTCOLORIZED && userKey != EXIT)

	{
		if (userKey == 0)
			printMenu();

		userKey = _getch();
		if (userKey == INSTRUCTIONS)
			printInstructions();
		if (userKey == STARTCOLORIZED)
		{
			gameColorized = true;
			setGameColors();
		}
	}

	system("cls");
	//Sleep(100);
}

void ThePacmanGame::setGameColors()
{
	game_board.setBorderColor(gameColors::LIGHTCYAN);
	game_board.setBreadcrumbColor(gameColors::GREEN);
	game_board.settunnelColor(gameColors::RED);
	pacman.setPacColor(gameColors::YELLOW);
	for (auto& gh : ghost)
		gh.setGhostColor(gameColors::BLUE);
}

void ThePacmanGame::printMenu()
{
	cout << "Welcome to Pacman game!" << endl;
	cout << "Press (1) to Start without colors" << endl;
	cout << "Press (2) to Start with colors" << endl;
	cout << "Press (8) for Instructions" << endl;
	cout << "press (9) to exit" << endl;
}

void ThePacmanGame::printInstructions()
{
	system("cls");

	cout << "Welcome to Pacman game!" << endl;
	cout << "Pac - MAN has 3 life in this game." << endl;
	cout << "Pac - MAN will gain points by collecting all the breadcrumbs in the maze." << endl;
	cout << "You should avoid any interactions with the ghosts. Otherwise, you will be eaten and lose lives." << endl;
	cout << "To win the game you should eat ALL the breadcrumbs" << endl;
	cout << endl;
	cout << endl;
	cout << "Keys instruction: " << endl;
	cout << "Move UP: press w or W " << endl;
	cout << "Move DOWN: press x or X" << endl;
	cout << "Move LEFT: press a or A" << endl;
	cout << "Move RIGHT: press d or D" << endl;
	cout << "To STAY in your position: press s or S" << endl;
	cout << "Good Luck!" << endl;
	cout << endl;
	cout << "Press ESC to return the main menu." << endl;

	while (userKey != ESC)
		userKey = _getch();

	system("cls");
	userKey = 0;
}

//Running a game session, according to do-while loop condition
void ThePacmanGame::runGame()
{
	char key = 0;
	Direction currDir;

	do
	{
		if (_kbhit())
		{
			key = _getch();
			currDir = pacman.getDirection(key); //A kind of key validation.
			if (currDir != Direction::WRONG_KEY)
				pacman.setDirection(currDir);
		}
		singleGhostsSession();
		singlePacmanSession();
		//printFigures();

		if (key == ESC)
		{
			pauseGame();
			key = 0; //So pacman will continue as he was before pausing.
		}

		Sleep(75);

	} while (!GameFinished());

	if (gameColorized) { resetColors(); }
	gotoxy(0, 30);
	printResult();
	system("cls");

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

	printGhosts();
}

void ThePacmanGame::singlePacmanSession()
{
	pacman.movePacman(game_board);
	pacman.updatePos();

	if (!checkCollision())
		pacman.updateScore(game_board);
	else
		resetAfterCollision();

	pacman.printPacman();
}

void ThePacmanGame::printGhosts()
{
	for (auto& gh : ghost)
		gh.printGhost();
}

void ThePacmanGame::printFigures()
{
	//pacman.printPacman();
	/*for (auto& gh : ghost)
		gh.printGhost();*/
}

void ThePacmanGame::pauseGame()
{
	char key;

	gotoxy(20, 25);
	cout << "Game paused, press ESC again to continue";

	key = _getch();

	while (key != ESC)// not ESC, to continue
		key = _getch();

	gotoxy(20, 25);
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
	Sleep(1000);
}

void ThePacmanGame::printCellRestore()
{
	char cell;
	int x, y;

	x = pacman.getCurrPos().getXPos();
	y = pacman.getCurrPos().getYPos();
	cell = game_board.getCellInBoard(x, y);
	if (cell == BREADCRUMB && game_board.getBreadcrumbColor() != gameColors::WHITE) { setTextColor(game_board.getBreadcrumbColor()); }
	gotoxy(x, y);
	cout << cell;

	for (auto& gh : ghost)
	{
		x = gh.getCurrPos().getXPos();
		y = gh.getCurrPos().getYPos();
		cell = game_board.getCellInBoard(x, y);
		//gh.getCurrPos().gotoxy(x, y);
		gotoxy(x, y);
		cout << cell;
	}

}
void ThePacmanGame::printLives()
{
	gotoxy(32, 27);
	cout << "Lives Left: " << pacman.getLivesLeft();
}

bool ThePacmanGame::GameFinished()
{
	if (pacman.getLivesLeft() > 0 && game_board.getBreadcrumbs() != pacman.getScore())
		return false;
	if (pacman.getLivesLeft() == 0)
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
		cout << "GAME OVER Shiback, your final score is: " << pacman.getScore() << endl;

	cout << "Thanks for playing" << endl;

	Sleep(2000);
}