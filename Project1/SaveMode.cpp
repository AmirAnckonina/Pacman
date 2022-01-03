#include "SaveMode.h"

void SaveMode::run()
{
	cout << "Hey, SaveMode" << endl;
	Sleep(2000);
	clearScreen();
	runAllSessions();
}

void SaveMode::openFilesForWriting()
{
	string stepsFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate() - 1).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate() - 1).size() - 6)) + "steps";
	string resultFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate() - 1).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate() - 1).size() - 6)) + "result";
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
			int x = fruit.getCurrPos().getXPos();
			int y = fruit.getCurrPos().getYPos();

			if (x < 10)
			{
				stepsFile << '0' << fruit.getCurrPos().getXPos();
			}
			else
			{
				stepsFile << fruit.getCurrPos().getXPos();
			}
			stepsFile << ',';

			if (y < 10)
			{
				stepsFile << '0' << fruit.getCurrPos().getYPos();
			}
			else
			{
				stepsFile << fruit.getCurrPos().getYPos();
			}

			stepsFile << ") | ";
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
		countsteps++;

		singlePlayerIteration();
		singleCreaturesIteration();
		//Steps
		writeMovesToStepsFile();
		writeToResultFileDuringSession();
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
	if (collisionInCurrStepIndicator == true)
	{
		resultFile << "Pacman eaten on step: " << countsteps;
		resultFile << '\n';
		collisionInCurrStepIndicator = false;
	}

}

void SaveMode::closeFiles()
{
	stepsFile.close();
	resultFile.close();
}
