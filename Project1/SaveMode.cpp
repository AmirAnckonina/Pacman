#include"SaveMode.h"

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
		dir = "UP";
		break;
	case Direction::DOWN:
		dir = "DOWN";
		break;
	case Direction::LEFT:
		dir = "LEFT";
		break;
	case Direction::RIGHT:
		dir = "RIGHT";
		break;
	case Direction::STAY:
		dir = "STAY";
		break;

	}
}

void SaveMode::writeMovesToStepsFile()
{
	stepsFile << "Pacman: ";
	convertDirToInput(pacman.getDirection());
	stepsFile << dir << '|';

	for (int i = 0; i < numOfGhosts; i++)
	{
		stepsFile << "ghost " << i << ': ';
		convertDirToInput(ghost[i].getDirection());
		stepsFile << dir << '|';
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
	do
	{
		singlePlayerIteration();
		singleCreaturesIteration();
		//steps
		writeMovesToStepsFile();
	} while (!GameFinished());

	afterRunGameProcedure();
	closeFiles();
	//result
}



void SaveMode::writeToresultFile()
{
	resultFile << "Died in step: ";
	resultFile << countsteps;
	resultFile << '\n';
	if (pacman.getLivesLeft() == 0)
	{
		resultFile << " lose the game on step: " << countsteps << '\n';
		resetStepsCounter();
	}


}

void SaveMode::closeFiles()
{
	stepsFile.close();
	resultFile.close();
}
