#include "ThePacmanGame.h"

bool ThePacmanGame::gameColorized = false;

void ThePacmanGame::startGameSessions()
{
	bool activate = true;
	while (activate)
	{
		entryMenu();
		if (userKey == EXIT)
			activate = false;
		else
		{
			initGame();
			Sleep(10000);
			//runGame();
		}
	}
	cout << "Goodbye" << endl;
}

void ThePacmanGame::entryMenu()
{
	clearInput();
	cout << "Press any key to enter the game menu..." << endl;
	userKey = _getch();
	userKey = 0;
	clearScreen();

	while (!userChoosedToStart())
	{
		printMenu();
		userKey = _getch();
		if (userKey == INSTRUCTIONS)
			printInstructions();
		else if (userKey == STARTCOLORIZED)
			gameColorized = true;
		else
			gameColorized = false;
	}
	clearScreen();
}
//Creating board which hold the information of every cell
//Creating creatures, initialize lives, set colors, printing rules, instructions, etc.
void ThePacmanGame::initGame()
{
	hideCursor();
	game_board.initBoard();
	//pacman.initPacman();
	/*ghost[0].initGhost(40, 9);
	ghost[1].initGhost(40, 15);
	if (gameColorized) 
		setGameColors();
	else 
		detailsColor = Colors::WHITE;
	ghostsTurn = playerWon = false;
	game_board.printBoard();
	pacman.printPacman();
	printGameName();
	printLives();
	printAllGhosts();*/
}

void ThePacmanGame::printMenu() const
{
	gotoxy(0, 0);
	cout << "Welcome to Pacman game!" << endl;
	cout << "Press (1) to Start without colors" << endl;
	cout << "Press (2) to Start with colors" << endl;
	cout << "Press (8) for Instructions" << endl;
	cout << "press (9) to exit" << endl;
}

void ThePacmanGame::printInstructions() 
{
	clearScreen();

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

	clearScreen();
	userKey = 0;
}

bool ThePacmanGame::userChoosedToStart() const
{
	if (userKey == START || userKey == STARTCOLORIZED || userKey == EXIT)
		return true;
	else 
		return false;
}

void ThePacmanGame::setGameColors()
{
	detailsColor = Colors::YELLOW;
	game_board.setBorderColor(Colors::GRAY);
	game_board.setBreadcrumbColor(Colors::BROWN);
	game_board.settunnelColor(Colors::YELLOW);
	pacman.setPacColor(Colors::YELLOW);
	for (auto& gh : ghost)
		gh.setGhostColor(Colors::LIGHTBLUE);
}

//Running a game session, according to do-while loop condition
void ThePacmanGame::runGame()
{
	char key = 0;
	Direction currDir;
	do
	{
		if (key == ESC)
		{
			pauseGame();
			key = 0; //So pacman will continue as he was before pausing.
		}

		singleGhostsSession();
		singlePacmanSession();
		printFigures();
		Sleep(90);

		if (_kbhit())
		{
			key = _getch();
			currDir = pacman.getDirection(key); //A kind of key translation to move.
			if (currDir != Direction::WRONG_KEY)
				pacman.setDirection(currDir);
		}

	} while (!GameFinished());

	printResult();
	if (gameColorized) { resetColors(); }
	clearScreen();
	Sleep(1200);
}

void ThePacmanGame::singlePacmanSession()
{
	if (pacman.getLivesLeft() > 0)
	{
		pacman.movePacman(game_board);
		pacman.updatePos();

		if (!checkCollision())
		{
			pacman.updateScore(game_board);
			singlePrintScore();
			Position tmpPos = pacman.getCurrPos();
			game_board.setCellInBoard(tmpPos, GameBoard::SPACE);
		}
		else
			resetAfterCollision();
	}
}

void ThePacmanGame::singlePrintScore() const
{
	gotoxy(21, 13);
	cout << "                                       " << endl;
	if (gameColorized)
		setTextColor(detailsColor);
	gotoxy(32, 13);
	cout << "The score is = " << pacman.getScore();
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
		ghostsTurn = false; //they won't move in the next step
	}
	else 
		ghostsTurn = true;

	if (checkCollision())
		resetAfterCollision();
}

void ThePacmanGame::printAllGhosts() const
{
	for (auto& gh : ghost)
		gh.printGhost();
}

void ThePacmanGame::printFigures() const
{
	pacman.printPacman();
	printAllGhosts();
}

void ThePacmanGame::pauseGame() const
{
	char key;

	gotoxy(24, 11);
	if (gameColorized)
		setTextColor(detailsColor);
	cout << "Game paused, press ESC to continue";
	key = _getch();

	while (key != ESC)
		key = _getch();

	gotoxy(21, 11);
	cout << "                                       " << endl;//remove pause message
	printGameName();
}

bool ThePacmanGame::checkCollision() const
{
	int pac_x, gh_x, pac_y, gh_y; //More convient and readable.
	pac_x = pacman.getCurrPos().getXPos();
	pac_y = pacman.getCurrPos().getYPos();
	for (auto& gh : ghost)
	{
		gh_x = gh.getCurrPos().getXPos();
		gh_y = gh.getCurrPos().getYPos();
		if (pac_x == gh_x && pac_y == gh_y)
		{
			printCollision();
			return true;
		}
	}
	return false;
}

void ThePacmanGame::resetAfterCollision()
{

	printCellRestore();
	pacman.updateLivesLeft();
	printLives();
	if (pacman.getLivesLeft() > 0)
	{
		pacman.setPacmanPosition();
		ghost[0].setGhostPosition(40, 9);
		ghost[1].setGhostPosition(40, 15);
		pacman.printPacman();
		printAllGhosts();
		Sleep(500);
		printRSG();
		printGameName();
		//Prevent the pacman to run immidiatley,
		//So if any direction key pressed while the reset messages printed will be ignored.
		clearInput();
	}
}

void ThePacmanGame::printCellRestore() const
{
	char cell;
	int x, y;

	x = pacman.getCurrPos().getXPos();
	y = pacman.getCurrPos().getYPos();
	cell = game_board.getCellInBoard(x, y);
	if (cell == GameBoard::BREADCRUMB && gameColorized) 
		setTextColor(game_board.getBreadcrumbColor());
	gotoxy(x, y);
	cout << cell;

	//Handle it and restore to all ghosts
	for (auto& gh : ghost)
	{
		x = gh.getCurrPos().getXPos();
		y = gh.getCurrPos().getYPos();
		cell = game_board.getCellInBoard(x, y);
		if (cell == GameBoard::BREADCRUMB && gameColorized) 
			setTextColor(game_board.getBreadcrumbColor()); 
		gotoxy(x, y);
		cout << cell;
	}

}

void ThePacmanGame::printLives() const
{
	if (gameColorized)
		setTextColor(detailsColor);
	gotoxy(34, 12);
	cout << "Lives Left: " << pacman.getLivesLeft();
}

void ThePacmanGame::printGameName() const
{
	if (gameColorized)
		setTextColor(detailsColor);
	gotoxy(29, 11);
	cout << "  P  A  C  -  M  A  N  ";
}

void ThePacmanGame::printRSG() const
{
	if (gameColorized) setTextColor(detailsColor);

	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(37, 11);
	cout << "Ready,";
	Sleep(1200);
	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(38, 11);
	cout << "Set,";
	Sleep(1200);
	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(38, 11);
	cout << "GO!";
	Sleep(750);
	gotoxy(21, 11);
	cout << "                                       " << endl;
}

void ThePacmanGame::printCollision() const
{
	for (int i = 0; i < 5; i++)
	{
		printAllGhosts();
		Sleep(300);
		pacman.printPacman();
		Sleep(300);
	}
}

bool ThePacmanGame::GameFinished()
{
	if (pacman.getLivesLeft() > 0 && game_board.getBreadcrumbs() != pacman.getScore())
		return false;
	if (pacman.getLivesLeft() == 0)
		playerWon = false;
	else if (game_board.getBreadcrumbs() == pacman.getScore())
	{
		playerWon = true;
		pacman.printPacman(); //print pacman in the his last position, the winning one!
	}

	return true;
}

void ThePacmanGame::printResult() const
{
	Sleep(750);
	clearRectangle();
	if (playerWon == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (gameColorized)
				setTextColor(pacman.getPacColor());
			gotoxy(27, 12);
			cout << "Congratulations, You WON!" << endl;
			Sleep(750);
			gotoxy(21, 12);
			clearRectangle();
			Sleep(750);
		}
		printPacmanAllAround();
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (gameColorized) 
				setTextColor(ghost[0].getGhostColor());
			gotoxy(33, 12);
			cout << "GAME OVER!!!!" << endl;
			Sleep(500);
			clearRectangle();
			Sleep(500);
		}
		printGhostsAllAround();
	}
	if (gameColorized) 
		setTextColor(detailsColor);
	clearRectangle();
	gotoxy(27, 12);
	cout << "your final score is: " << pacman.getScore() << endl;
	Sleep(2500);
	clearRectangle();
	gotoxy(30, 12);
	cout << "Thanks for playing!" << endl;
	Sleep(3000);
}

void ThePacmanGame::clearRectangle() const
{
	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(21, 12);
	cout << "                                       " << endl;
	gotoxy(21, 13);
	cout << "                                       " << endl;
}

//Pacman animation at the end
void ThePacmanGame::printPacmanAllAround() const
{
	int x = 21, y = 11;
	if (gameColorized) setTextColor(pacman.getPacColor());
	while (x <= 59)
	{
		gotoxy(x++, y);
		cout << Pacman::PACMAN;
		Sleep(5);
	}
	x--;
	y++;
	while (x >= 21)
	{
		gotoxy(x--, y);
		cout << Pacman::PACMAN;
		Sleep(5);
	}
	x++;
	y++;
	while (x <= 59)
	{
		gotoxy(x++, y);
		cout << Pacman::PACMAN;
		Sleep(5);
	}

	Sleep(1500);			
}

//Ghost Animation at the end
void ThePacmanGame::printGhostsAllAround() const
{
	int x1 = 21, y1 = 11, x2 = 59, y2 = 13;
	if (gameColorized) setTextColor(ghost[0].getGhostColor());
	while (x1 <= 59 && x2 >= 21)
	{
		gotoxy(x1++, y1);
		cout << Ghost::GHOST;
		gotoxy(x2--, y2);
		cout << Ghost::GHOST;
		Sleep(5);
	}
	x1--; 
	y1++; 
	x2++;
	y2--;
	while (x2 <= x1)
	{
		gotoxy(x1--, y1);
		cout << Ghost::GHOST;
		gotoxy(x2++, y2);
		cout << Ghost::GHOST;
		Sleep(5);
	}
	Sleep(1500);
}
