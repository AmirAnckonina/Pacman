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
			if (game_menu.getUserKey() == Menu::STARTCOLORIZED)
				gameColorized = true;

			level = game_menu.getGameDifficulty();
			game_board.loadAllScreenTemplates();
			runAllGameBoards(activate);
		}
	}
	cout << "Goodbye" << endl;
}

void ThePacmanGame::runAllGameBoards(bool& activate)
{
	size_t numOfTemplates = game_board.getNumOfTemplates();

	for (int i = 0; i < numOfTemplates; i++)
	{
		initGame();
		runGame();
		//game_menu.

	}
}

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, set colors, printing rules, instructions, etc.
void ThePacmanGame::initGame()
{

	hideCursor();
	game_board.initBoard();
	game_menu.initDetailsArea(game_board);

	numOfGhosts = game_board.collectnumOfGhosts();
	pacman.initPacman(game_board);

	for (int i = 0; i < numOfGhosts; i++)
		ghost[i].initGhost(game_board, level);
	fruit.initFruit();

	if (gameColorized) setGameColors();
	else game_menu.setDetailsColor(Colors::WHITE);

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
	fruit.setColor(Colors::RED);
	for (int i = 0; i < numOfGhosts; i++)
		ghost[i].setColor(Colors::LIGHTBLUE);
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
			game_menu.pauseGame(pacman.getLivesLeft());
			key = 0; //So pacman will continue as he was before pausing.
		}
		singleFruitSession();
		singlePacmanSession();
		singleGhostsSession();
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
		pacman.move(game_board);
		pacman.updatePos();

		if (isFruitEatenByPacman())
		{
			//do nothing//

			//pacman.addFruitToScore(fruit.getFruitVal());
			//fruit.disableActivity();
			//generalCellRestore(fruit);
		}

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
void ThePacmanGame::singleFruitSession()
{
	if (fruit.isActive())
	{
		if (fruit.getTimeOnBoard() == 40)
		{
			fruit.generateLocation(game_board);
			fruit.generateFruitValue();
		}

		if (fruitTurn)
		{
			fruit.move(game_board);
			fruit.updatePos();
			fruitTurn = false; //it won't move in the next step
			fruit.ReduceTimeOnBoard();
		}
		else
			fruitTurn = true;

		if (isFruitEatenByPacman() || isFruitEatenByGhost())
		{
			fruitEatenProcedure();//when it becomes 
		}
		if (fruit.getTimeOnBoard() == 0)
		{
			fruit.disableActivity();
			generalCellRestore(fruit);

		}

	}
	else//fruit not active
	{
		fruit.ReduceTimeNotOnBoard();
		if (fruit.getTimeOffBoard() == 0)
			fruit.enableActivity();
	}
}
void ThePacmanGame::singleGhostsSession()
{
	//PAY attention, ghost should move every other turn. so the condition manage it.
	if (ghostsTurn)
	{
		for (int i = 0; i < numOfGhosts; i++)
		{
			ghost[i].move(game_board, pacman.getCurrPos());
			ghost[i].updatePos();
		}
		ghostsTurn = false; //they won't move in the next step
	}
	else
		ghostsTurn = true;
	if (isFruitEatenByGhost())
	{
		fruitEatenProcedure();
	}

	if (checkCollision())
		resetAfterCollision();
}

void ThePacmanGame::printAllGhosts() const
{
	for (int i = 0; i < numOfGhosts; i++)
		ghost[i].printCreature();
}

void ThePacmanGame::printFigures() const
{
	pacman.printCreature();
	printAllGhosts();
	if (fruit.isActive())
		fruit.printCreature();
}

bool ThePacmanGame::checkCollision() const
{
	for (int i = 0; i < numOfGhosts; i++)
	{
		if (pacman.getCurrPos() == ghost[i].getCurrPos())
		{
			printCollision();
			return true;
		}
	}
	return false;
}


void ThePacmanGame::fruitEatenProcedure()
{
	fruit.disableActivity();
	generalCellRestore(fruit);
	fruitTurn = true;
}
bool ThePacmanGame::isFruitEatenByPacman()
{

	if (pacman.getCurrPos() == fruit.getCurrPos() && fruit.isActive())
	{
		pacman.addFruitToScore(fruit.getFruitVal());
		return true;
	}

	return false;
}
bool ThePacmanGame::isFruitEatenByGhost()
{
	for (int i = 0; i < numOfGhosts; i++)
	{
		if ((ghost[i].getCurrPos() == fruit.getCurrPos()) && fruit.isActive())
		{
			if (pacman.getScore() >= 10)
				pacman.addFruitToScore((-1) * fruit.getFruitVal());
			//add a cool message on board
			else
				pacman.setScore(0);
			return true;
		}
	}

	return false;
}
void ThePacmanGame::resetAfterCollision()
{

	cellsRestoreAfterCollision();
	pacman.updateLivesLeft();
	game_menu.printLives(pacman.getLivesLeft());
	if (pacman.getLivesLeft() > 0)
	{
		pacman.resetCreaturePosition();
		//ghost[0].setGhostPosition(40, 9);
		for (int i = 0; i < numOfGhosts; i++)
			ghost[i].resetCreaturePosition();
		//ghost[1].setGhostPosition(40, 15);
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

void ThePacmanGame::cellsRestoreAfterCollision() const
{
	//cell = game_board.getCellInBoard(pacman.getCurrPos());
	////if (cell == GameBoard::BREADCRUMB && gameColorized) -- CHANGED!
	//if (cell == GameBoard::BREADCRUMB && gameColorized)
	//	setTextColor(game_board.getBreadcrumbColor());

	//gotoxy(pacman.getCurrPos().getXPos(), pacman.getCurrPos().getYPos());
	//cout << cell;

	generalCellRestore(pacman);

	//Handle it and restore to all ghosts
	for (int i = 0; i < numOfGhosts; i++)
	{

		//cell = game_board.getCellInBoard(ghost[i].getCurrPos()); //CHANGED!

		//if (cell == GameBoard::BREADCRUMB && gameColorized)
		//	setTextColor(game_board.getBreadcrumbColor());

		//gotoxy(ghost[i].getCurrPos().getXPos(), ghost[i].getCurrPos().getYPos());
		//cout << cell;

		generalCellRestore(ghost[i]);
	}

}

void ThePacmanGame::generalCellRestore(const Creature& creature) const
{
	char cell;

	cell = game_board.getCellInBoard(creature.getCurrPos());
	//if (cell == GameBoard::BREADCRUMB && gameColorized) -- CHANGED!
	if (cell == GameBoard::BREADCRUMB && gameColorized)
		setTextColor(game_board.getBreadcrumbColor());

	gotoxy(creature.getCurrPos().getXPos(), creature.getCurrPos().getYPos());
	cout << cell;
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
