#include "ThePacmanGame.h"

bool ThePacmanGame::gameColorized = false;

void ThePacmanGame::startGameSessions()
{
	bool activate = true;
	while (activate)
	{
		game_menu.entryMenu();
		if (game_menu.getUserKey() == Menu::EXIT)
			activate = false;
		else
		{
			if (game_menu.getUserKey() == Menu::STARTCOLORIZED) { gameColorized = true; }
			initGame();
			runGame();
		}
	}
	cout << "Goodbye" << endl;
}

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, set colors, printing rules, instructions, etc.
void ThePacmanGame::initGame()
{
	hideCursor();
	game_board.initBoard();
	game_menu.initDetailsArea(game_board);
	pacman.initPacman(game_board);
	ghost[0].initGhost(game_board);
	ghost[1].initGhost(game_board);
	if (gameColorized)
		setGameColors();
	else
		game_menu.setDetailsColor(Colors::WHITE);
	ghostsTurn = playerWon = false;
	game_board.printBoard();
	pacman.printCreature();
	game_menu.printGameName();
	game_menu.printLives(pacman.getLivesLeft());
	printAllGhosts();
}

void ThePacmanGame::setGameColors()
{
	game_menu.setDetailsColor(Colors::YELLOW);
	game_board.setBorderColor(Colors::GRAY);
	game_board.setBreadcrumbColor(Colors::BROWN);
	game_board.settunnelColor(Colors::YELLOW);
	pacman.setColor(Colors::YELLOW);
	for (auto& gh : ghost)
		gh.setColor(Colors::LIGHTBLUE);
}

//Running a game session, according to do-while loop condition
void ThePacmanGame::runGame()
{
	char key = 0;
	Direction currDir;
	do
	{
		if (key == Menu::ESC)
		{
			game_menu.pauseGame();
			key = 0; //So pacman will continue as he was before pausing.
		}

		singleGhostsSession();
		singlePacmanSession();
		printFigures();
		Sleep(90);

		if (_kbhit())
		{
			key = _getch();
			currDir = pacman.convertKeyToDirection(key); //A kind of key translation to move.
			if (currDir != Direction::WRONG_KEY)
				pacman.setDirection(currDir);
		}

	} while (!GameFinished());

	game_menu.printResult(playerWon, pacman.getScore(), pacman.getColor(), ghost[0].getColor());
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
			game_menu.singlePrintScore(pacman.getScore());
			game_board.setCellInBoard(pacman.getCurrPos(), GameBoard::SPACE);
		}
		else
			resetAfterCollision();
	}
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

void ThePacmanGame::printFigures() const
{
	pacman.printCreature();
	for (auto& gh : ghost)
		gh.printCreature();
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
		//if(pacman.getCurrPos() == gh.getCurrPos()) create opertor function!!!
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
	game_menu.printLives(pacman.getLivesLeft());
	if (pacman.getLivesLeft() > 0)
	{
		pacman.resetCreaturePosition();
		//ghost[0].setGhostPosition(40, 9);
		ghost[0].resetCreaturePosition();
		//ghost[1].setGhostPosition(40, 15);
		ghost[1].resetCreaturePosition();
		pacman.printCreature();
		printAllGhosts();
		Sleep(500);
		game_menu.printRSG();
		game_menu.printGameName();
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
	cell = game_board.getCellInBoard(pacman.getCurrPos());
	//if (cell == GameBoard::BREADCRUMB && gameColorized) -- CHANGED!
	if (cell == GameBoard::BREADCRUMB && gameColorized)
		setTextColor(game_board.getBreadcrumbColor());
	gotoxy(x, y);
	cout << cell;

	//Handle it and restore to all ghosts
	for (auto& gh : ghost)
	{
		cell = game_board.getCellInBoard(gh.getCurrPos()); //CHANGED!
		if (cell == GameBoard::BREADCRUMB && gameColorized)
			setTextColor(game_board.getBreadcrumbColor());
		gotoxy(x, y);
		cout << cell;
	}

}

void ThePacmanGame::printCollision() const
{
	for (int i = 0; i < 5; i++)
	{
		printAllGhosts();
		Sleep(300);
		pacman.printCreature();
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
		pacman.printCreature(); //print pacman in the his last position, the winning one!
	}

	return true;
}
