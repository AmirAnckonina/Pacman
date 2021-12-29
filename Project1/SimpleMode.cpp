//#pragma once
//
//#include "SimpleMode.h"
//#include "ThePacmanGame.h"
//
//void SimpleMode::openFilesForWriting()
//{
//	string stepsFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".steps";
//	string resultFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".result";
//	resultFile.open(resultFileName);
//	stepsFile.open(stepsFileName);
#include "ThePacmanGame.h"

bool ThePacmanGame::gameColorized = false;

void ThePacmanGame::runAllSessions()
{
	hideCursor();
	init_srand();

	activate = true;
	size_t totalNumOfScreens;

	game_board.loadAllScreenTemplates();
	totalNumOfScreens = game_board.getNumOfTemplates();
	game_menu.entryMenu();

	while (activate)
	{
		if (game_menu.getUserKey() == Menu::STARTCOLORIZED)
			gameColorized = true;

		if (game_menu.getUserKey() == Menu::EXIT)
			activate = false;

		if (activate)
		{
			runSingleSession(totalNumOfScreens);
			resetThePacmanGame();
		}

	}
	clearScreen();
	gotoxy(0, 0);
	cout << "Goodbye" << endl;
}

void ThePacmanGame::runSingleSession(size_t& totalNumOfScreens)
{
	bool shouldEndSession = false;
	int userChosenTemplate = game_menu.getFirstBoardChoice(game_board);
	game_board.sortByFirstBoardChosen(userChosenTemplate);

	for (int templateInd = 0; templateInd < totalNumOfScreens && !shouldEndSession && activate; templateInd++)
	{
		if (game_menu.getUserKey() == Menu::EXIT)
			activate = false;
		else
		{
			if (game_menu.getUserKey() == Menu::STARTCOLORIZED)
				gameColorized = true;

			level = game_menu.getGameDifficulty();
			initGame();
			if (game_board.isValidBoard())
			{
				runGame();
				if (pacman.getLivesLeft() == 0)
					shouldEndSession = true;

			}
			game_shell.betweenSessionsProcedure(game_board, templateInd, pacman.getScore(), playerWon);
			game_menu.entryMenu();
		}
	}
}

void ThePacmanGame::resetThePacmanGame()
{
	pacman.resetScoreAndLives();
	game_board.lexSort();
	game_board.resetCurrTemplate();
	playerWon = false;
}

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, set colors, printing rules, instructions, etc.
void ThePacmanGame::initGame()
{
	hideCursor();
	init_srand();
	game_board.initBoard();

	if (game_board.isValidBoard())
	{
		game_shell.initDetailsArea(game_board);
		numOfGhosts = game_board.collectnumOfGhosts();
		pacman.initPacman(game_board, Creature::PACMAN);

		for (int i = 0; i < numOfGhosts; i++)
			ghost[i].initGhost(game_board, level);

		fruit.initFruit();
		game_board.countTotalBreadcrumbs();
		game_board.setBreadCrumbsPosArr();

		if (gameColorized) setGameColors();
		else game_shell.setDetailsColor(Colors::WHITE);

		playerWon = false;

		printAfterInit();
	}
}

void ThePacmanGame::printAfterInit()
{
	game_board.printBoard();
	pacman.printCreature();
	game_shell.printAllLegend(pacman.getScore(), pacman.getLivesLeft());
	printAllGhosts();
}

void ThePacmanGame::setGameColors()
{
	game_shell.setDetailsColor(Colors::LIGHTGREEN);
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
			game_shell.pauseGame(pacman.getLivesLeft());
			key = 0; //So pacman will continue as he was before pausing.
		}
		singleGhostsSession();
		singlePacmanSession();
		completePacmanSession();
		singleFruitSession();
		printFigures();
		Sleep(120);

		if (_kbhit())
		{
			key = _getch();
			currDir = pacman.convertKeyToDirection(key); //A kind of key translation to move.
			if (currDir != Direction::WRONG_KEY)
				pacman.setDirection(currDir);
		}

	} while (!GameFinished());

	game_shell.printResult(playerWon, pacman.getScore(), pacman.getColor(), ghost[0].getColor());
	if (gameColorized) { resetColors(); }
	gameColorized = false;
	clearScreen();
	Sleep(1200);
}

void ThePacmanGame::singlePacmanSession()
{
	if (pacman.getLivesLeft() > 0)
	{
		pacman.move(game_board);
		pacman.updatePrevPos();
		pacman.updatePos();

		pacman.afterMoveProcedure(game_board);
	}

}

void ThePacmanGame::completePacmanSession()
{
	if (isFruitEatenByPacman())
		fruitEatenProcedure();

	if (!checkCollision())
	{
		pacman.updateScore(game_board);
		if (game_board.getCellInBoard(pacman.getNextPos()) == GameBoard::BREADCRUMB)
			game_board.reduceNumOfBreadCrumbs(); // should check if we ate breadcrumb\

		if (game_board.getCellInBoard(pacman.getCurrPos()) != GameBoard::TUNNEL)
			game_board.setCellInBoard(pacman.getCurrPos(), GameBoard::SPACE);

	}
	else
		resetAfterCollision();
}


void ThePacmanGame::singleFruitSession()
{
	if (fruit.isActive())
	{
		//Only for Simple - Save
		if (fruit.getTimeOnBoard() == 40)
		{
			fruit.generateLocation(game_board);
			fruit.generateFruitValue();
			fruit.ReduceTimeOnBoard();
		}


		if (fruitTurn)
		{
			//To all modes
			fruit.move(game_board);
			fruit.afterMoveProcedure(game_board);
			fruit.updatePos();
			//Only for simple-save
			fruit.ReduceTimeOnBoard();
			fruitTurn = false; //it won't move in the next step
		}
		else
			fruitTurn = true;


		if (isFruitEatenByPacman() || isFruitEatenByGhost())
			fruitEatenProcedure();//when it becomes 

		fruit.printCreature();

		if (fruit.getTimeOnBoard() == 0)
		{
			fruit.disableActivity();
			generalCellRestore(fruit);
		}

	}
	else
	{
		fruit.ReduceTimeOffBoard();
		if (fruit.getTimeOffBoard() == 0)
			fruit.enableActivity();
	}
}

void ThePacmanGame::singleGhostsSession()
{
	static int j = 0;

	//PAY attention, ghost should move every other turn. so the condition manage it.
	//Splitted to odd and even ghosts indexes, in order to ease the BFS algorithem.
	for (int i = j; i < numOfGhosts; i += 2)
	{
		ghost[i].move(game_board, pacman.getCurrPos());
		ghost[i].afterMoveProcedure(game_board);
		ghost[i].updateIntervalInStrategyIfNeeded();
		ghost[i].updatePos();
	}
	if (j == 0)
		j = 1;
	else
		j = 0; //they won't move in the next step

	if (isFruitEatenByGhost())
		fruitEatenProcedure();

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
}

bool ThePacmanGame::checkCollision() const
{
	bool res = false;
	for (int i = 0; i < numOfGhosts; i++)
	{
		if (pacman.getCurrPos() == ghost[i].getCurrPos())
		{
			res = true;
		}
	}

	if (res == true) printCollision();
	return res;
}

void ThePacmanGame::fruitEatenProcedure()
{
	generalCellRestore(fruit);
	fruit.disableActivity();
	fruitTurn = true;
}

bool ThePacmanGame::isFruitEatenByPacman()
{
	if (pacman.getCurrPos() == fruit.getCurrPos() && fruit.isActive())
	{
		pacman.addFruitToScore(fruit.getFruitVal());

		if (fruit.getFruitVal() == 9)
			pacman.increaseLivesLeft();
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
				pacman.addFruitToScore((-1) * fruit.getFruitVal()); //add a cool message on board
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
	game_shell.printLives(pacman.getLivesLeft());
	if (pacman.getLivesLeft() > 0)
	{
		pacman.resetCreaturePosition();
		for (int i = 0; i < numOfGhosts; i++)
			ghost[i].resetCreaturePosition();

	}
	afterCollisionPrinting();
}
void ThePacmanGame::afterCollisionPrinting()
{
	if (pacman.getLivesLeft() > 0)
	{
		pacman.printCreature();
		printAllGhosts();
		Sleep(500);
		game_shell.printRSG();
		game_shell.printGameName();
		//Prevent the pacman to run immidiatley,
		//So if any direction key pressed while the reset messages printed will be ignored.
		clearInput();
	}
}
void ThePacmanGame::cellsRestoreAfterCollision() const
{
	generalCellRestore(pacman);
	//Handle it and restore to all ghosts
	for (int i = 0; i < numOfGhosts; i++)
	{
		generalCellRestore(ghost[i]);
	}
}

void ThePacmanGame::generalCellRestore(const Creature& creature) const
{
	char cell;

	cell = game_board.getCellInBoard(creature.getCurrPos());
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
	if (pacman.getLivesLeft() > 0 && game_board.getBreadcrumbs() > 0)
		return false;
	if (pacman.getLivesLeft() == 0)
		playerWon = false;
	if (game_board.getBreadcrumbs() == 0)
	{
		playerWon = true;
		pacman.printCreature(); //print pacman in the his last position, the winning one!
	}
	return true;
}
