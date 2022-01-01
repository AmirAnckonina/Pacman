#include "SaveMode.h"

void SaveMode::run()
{
	cout << "Hey, SaveMode" << endl;
	Sleep(2000);
	clearScreen();
	runAllSessions();
}
/*
void SaveMode::runAllSessions()
{
	preparations();
	while (activate)
	{
		presentMenu();
		handleSetGameColorized();
		firstBoardProcedure();
		runSingleScreensSession();
		resetThePacmanGame();
	}
	goodBye();
}

void SaveMode::runSingleScreensSession()
{
	pacmanDied = false;
	for (currScreenInd = 0; currScreenInd < totalNumOfScreens && !pacmanDied && activate; currScreenInd++)
	{
		handleQuit();
		initSingleScreen();
		runSingleScreen();
		game_shell.betweenScreensProcedure(game_board, currScreenInd, pacman.getScore(), playerWon);
		//game_menu.entryMenu();
	}
	//resetThePacmanGame();
}

void SaveMode::runSingleScreen()
{
	if (game_board.isValidBoard())
	{
		runGame();
		if (pacman.getLivesLeft() == 0)
			pacmanDied = true;
	}
}
*/
void SaveMode::openFilesForWriting()
{
	string stepsFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".steps";
	string resultFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".result";
	resultFile.open(resultFileName);
	stepsFile.open(stepsFileName);
}

void SaveMode::convertDirToInput(Direction _dir)
{
	switch (_dir)
	{
	case Direction::UP:
		dir = "UP   ";
		break;
	case Direction::DOWN:
		dir = "DOWN ";
		break;
	case Direction::LEFT:
		dir = "LEFT ";
		break;
	case Direction::RIGHT:
		dir = "RIGHT";
		break;
	case Direction::STAY:
		dir = "STAY ";
		break;

	}
}
void SaveMode::writeMovesToStepsFile()
{
	stepsFile << "Pacman: ";
	convertDirToInput(pacman.getDirection());
	stepsFile << dir << '\n';

	for (int i = 0; i < numOfGhosts; i++)
	{
		stepsFile << "Ghost" << i << ": ";
		convertDirToInput(ghost[i].getDirection());
		stepsFile << dir << '\n';
	}
	stepsFile << "Fruit:  ";
	if (!fruit.isActive())
	{
		stepsFile << "OFF";
	}
	else
	{
		convertDirToInput(fruit.getDirection());
		stepsFile << dir;
		if (fruit.getTimeOnBoard() == 39)
		{
			stepsFile << '|' << '(';
			stepsFile << fruit.getCurrPos().getXPos() << ',' << fruit.getCurrPos().getYPos() << ") | ";
			stepsFile << fruit.getFruitVal();
		}
	}
	stepsFile << '\n';
}

//Running a game session, according to do-while loop condition
void SaveMode::runGame()
{
	openFilesForWriting();
	do
	{
		singlePlayerIteration();
		singleCreaturesIteration();
		//steps
		writeMovesToStepsFile();
	} while (!GameFinished());

	writeToResultFileEndOfSession();
	afterRunGameProcedure();
	closeFiles();
	//result
}

void SaveMode::writeToResultFileEndOfSession()
{
	if (playerWon == true)
		resultFile << "1.Congrats, you finished the board on step: " << countsteps;
	else
		resultFile << "2.You lost on step: " << countsteps;
	resultFile << '\n';
}
void SaveMode::writeToResultFileInvalidBoard()
{
	if (!game_board.isValidBoard())
		resultFile << "3.Invalid board" << '\n';
}

void SaveMode::writeToResultFileDuringSession()
{
	resultFile << "Pacman eaten on step: " << countsteps;
	resultFile << '\n';
}

void SaveMode::closeFiles()
{
	stepsFile.close();
	resultFile.close();
}
