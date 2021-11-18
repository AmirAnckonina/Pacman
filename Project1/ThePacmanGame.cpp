#include "ThePacmanGame.h"

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, printing rules and instructions.
void ThePacmanGame::initGame()
{

	hideCursor();
	game_board.initBoard();
	pacman.initPacman();
	ghost[0].initGhost(40, 9);//was 40,9
	ghost[1].initGhost(40, 15);//was 40,15
	if (gameColorized) { setGameColors(); }
	else detailsColor = gameColors::WHITE;
	game_board.printBoard();
	pacman.printPacman();
	printLives();
	for (auto& gh : ghost)
		gh.printGhost();
}

void ThePacmanGame::entryMenu()
{
	cout << "Press any key to enter the game menu..." << endl;
	userKey = _getch();
	userKey = 0;

	while (!userChoosedToStart())
	{
		if (userKey == 0)
			printMenu();

		userKey = _getch();
		if (userKey == INSTRUCTIONS)
			printInstructions();
		if (userKey == STARTCOLORIZED) gameColorized = true;
		else gameColorized = false;
	}

	system("cls");
}

bool ThePacmanGame::userChoosedToStart()
{
	if (userKey == START || userKey == STARTCOLORIZED || userKey == EXIT)
		return true;
	else return false;
}

void ThePacmanGame::setGameColors()
{
	detailsColor = gameColors::YELLOW;
	game_board.setBorderColor(gameColors::GRAY);
	game_board.setBreadcrumbColor(gameColors::BROWN);
	game_board.settunnelColor(gameColors::YELLOW);
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
		printFigures();


		if (key == ESC)
		{
			pauseGame();
			key = 0; //So pacman will continue as he was before pausing.
		}
		Sleep(75);
		if (_kbhit())
		{
			key = _getch();
			currDir = pacman.getDirection(key); //A kind of key validation.
			if (currDir != Direction::WRONG_KEY)
				pacman.setDirection(currDir);
		}
		singleGhostsSession();
		singlePacmanSession();


	} while (!GameFinished());

	gotoxy(0, 30);
	//system("cls");
	printResult();
	Sleep(1200);
	if (gameColorized) { resetColors(); }
	system("cls");

}

void ThePacmanGame::singleGhostsSession()
{
	//PAY attention, ghost should move every other turn. so the condition manage it.
	if (ghostsTurn)
	{
		for (auto& gh : ghost)
		{
			gh.moveGhost(game_board);
			gh.updatePos();
		}

		if (checkCollision())
			resetAfterCollision();

		ghostsTurn = false; //they won't move in the next step
	}
	else 
		ghostsTurn = true;

	printAllGhosts();
}

void ThePacmanGame::printAllGhosts() const
{
	for (auto& gh : ghost)
		gh.printGhost();
}

void ThePacmanGame::singlePacmanSession()
{
	pacman.movePacman(game_board);
	pacman.updatePos();

	if (!checkCollision())
	{
		pacman.updateScore(game_board);
		gotoxy(32, 13);
		cout << "                            ";
		if (detailsColor != gameColors::WHITE)
			setTextColor(detailsColor);
		gotoxy(32, 13);
		cout << "The score is = " << pacman.getScore();
	}
	else
		resetAfterCollision();
	//pacman.printPacman();
}


void ThePacmanGame::pauseGame()
{
	char key;

	gotoxy(24, 11);
	if (detailsColor != gameColors::WHITE)
		setTextColor(detailsColor);
	cout << "Game paused, press ESC to continue";

	key = _getch();

	while (key != ESC)// not ESC, to continue
		key = _getch();

	gotoxy(24, 11);
	cout << "                                   ";//remove everything that was written
}


bool ThePacmanGame::checkCollision()
{
	int pac_x, gh_x, pac_y, gh_y; //More convient and readable.

	pac_x = pacman.getCurrPos().getXPos();
	pac_y = pacman.getCurrPos().getYPos();

	for (auto& gh : ghost)
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
	pacman.setPacmanPosition();
	pacman.updateLivesLeft();
	ghost[0].setGhostPosition(40, 9);//was (40,9)
	ghost[1].setGhostPosition(40, 15);
	printLives();
	pacman.printPacman();
	printAllGhosts();
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
		if (cell == BREADCRUMB && game_board.getBreadcrumbColor() != gameColors::WHITE) { setTextColor(game_board.getBreadcrumbColor()); }
		gotoxy(x, y);
		cout << cell;
	}

}
void ThePacmanGame::printLives()
{
	if (detailsColor != gameColors::WHITE)
		setTextColor(detailsColor);
	gotoxy(32, 12);
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
	gotoxy(25, 11);
	cout << "                              ";
	gotoxy(25, 12);
	cout << "                              ";
	gotoxy(25, 13);
	cout << "                              ";

	if (playerWon == true)
	{
		Sleep(500);
		gotoxy(23, 11);
		cout << "Congratulations, You WON!" << endl;
		Sleep(750);
		gotoxy(23, 12);
		cout << "your score is: " << pacman.getScore() << endl;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			gotoxy(23, 11);
			cout << "GAME OVER!!!!" << endl;
			Sleep(500);
			gotoxy(23, 11);
			cout << "             " << endl;
			Sleep(500);
		}
		gotoxy(23, 11);
		cout << "your final score is : " << pacman.getScore() << endl;

	}
	Sleep(750);
	gotoxy(23, 13);
	cout << "Thanks for playing" << endl;
	Sleep(2000);

}
void ThePacmanGame::printFigures()
{
	pacman.printPacman();
	for (auto& gh : ghost)
		gh.printGhost();
}