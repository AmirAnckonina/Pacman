#include "ThePacmanGame.h"

bool ThePacmanGame::gameColorized = false;

//Creating board which hold the information of every cell
//Creating creatures, initialize lives, set colors, printing rules, instructions, etc.
void ThePacmanGame::initGame(int ghostLevel)
{
	game_board.initBoard();
	if (game_board.isValidBoard())
	{
		game_shell.initDetailsArea(game_board);
		numOfGhosts = game_board.collectnumOfGhosts();
		pacman.initCreature(game_board, Creature::PACMAN);

		for (int i = 0; i < numOfGhosts; i++)
			ghost[i].initGhost(game_board, ghostLevel);

		fruit.initFruit();
		game_board.countTotalBreadcrumbs();
		game_board.setBreadCrumbsPosArr();

		if (gameColorized) setGameColors();
		else game_shell.setDetailsColor(Colors::WHITE);

		playerWon = false;
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

void ThePacmanGame::singlePacmanSession()
{
	if (pacman.getLivesLeft() > 0)
	{
		pacman.move(game_board);
		pacman.updatePrevPos();
		pacman.updatePos();
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
		collisionProcedure();
}


void ThePacmanGame::singleGhostsSession()
{

	//PAY attention, ghost should move every other turn. so the condition manage it.
	//Splitted to odd and even ghosts indexes, in order to ease the BFS algorithem.
	for (int i = j; i < numOfGhosts; i += 2)
	{
		ghost[i].move(game_board, pacman.getCurrPos());

		ghost[i].updateIntervalInStrategyIfNeeded();
		ghost[i].updatePrevPos();
		ghost[i].updatePos();
	}
}

void ThePacmanGame::afterGhostMove()
{
	for (int i = j; i < numOfGhosts; i += 2)
		ghost[i].afterMoveProcedure(game_board);
	if (j == 0)
		j = 1;
	else
		j = 0; //they won't move in the next step

}

//void ThePacmanGame::completeGhostSession()
//{
//	
//
//	
//}

void ThePacmanGame::printAllGhosts() const
{
	for (int i = 0; i < numOfGhosts; i++)
		ghost[i].printCreature();
}

void ThePacmanGame::printFigures() const
{
	game_shell.printAllLegend(pacman.getScore(), pacman.getLivesLeft());
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
	return res;
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

void ThePacmanGame::collisionProcedure()
{
	pacman.updateLivesLeft();
	if (pacman.getLivesLeft() > 0)
	{
		pacman.resetCreaturePosition();
		for (int i = 0; i < numOfGhosts; i++)
			ghost[i].resetCreaturePosition();
	}
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
		//pacman.printCreature(); //print pacman in the his last position, the winning one!
	}
	return true;
}
