#include "LoadMode.h"

void LoadMode::run()
{
	cout << "Hey, LoadMode" << endl;
	Sleep(2000);
	clearScreen();
	runAllSessions();
}

void LoadMode::runAllSessions()
{
	loadScreens();
	runSingleScreensSession();
	goodBye();
}

void LoadMode::runSingleScreensSession()
{
	pacmanDied = false;

	for (currScreenInd = 0; currScreenInd < totalNumOfScreens && !pacmanDied && activate; currScreenInd++)
	{
		initSingleScreen();
		runSingleScreen();
		game_shell.betweenScreensProcedure(game_board, currScreenInd, pacman.getScore(), playerWon);
	}
}

void LoadMode::runGame()
{

	return;
}

void LoadMode::singleFruitSession()
{
	return;
}

void LoadMode::loadAllStepsAndResultFiles()
{
	string path;
	for (const auto& file : filesystem::directory_iterator("."))
	{
		if (file.path().string().ends_with(".steps"))
		{
			path = file.path().string();
			path.erase(0, 2);
			stepsfilesArr.push_back(path);
		}
		else if (file.path().string().ends_with(".result"))
		{
			path = file.path().string();
			path.erase(0, 2);
			resultfilesArr.push_back(path);
		}
	}
	std::sort(stepsfilesArr.begin(), stepsfilesArr.end());
	std::sort(resultfilesArr.begin(), resultfilesArr.end());
}

void LoadMode::openFilesForRead()
{
	stepsFile.open(stepsfilesArr[currStepsFile]);
	resultFile.open(stepsfilesArr[currResultFile]);
}

void LoadMode::closeCurrFiles()
{
	stepsFile.close();
	resultFile.close();
}

void LoadMode::readInfoFromStepsFile()
{
	string line;
	string subStr;
	setPacDirectionFromFile();
	setGhostsDirectionFromFile();
	setFruitDirectionFromFile();
}
int LoadMode::convertStrToNum(string numToConvert)
{
	int res = 0;
	int i = 0;
	while (numToConvert[i] != '\n')
	{
		if (isdigit(numToConvert[i]))
		{
			res += res * 10 + numToConvert[i] - '0';
		}
	}
	return res;
}
void LoadMode::setPacDirectionFromFile()
{
	string line;
	string subStr;
	getline(stepsFile, line);
	subStr = line.substr(8, 12);
	convertInputToDirection(subStr);
	pacman.setDirection(direction);
}
void LoadMode::setGhostsDirectionFromFile()
{
	string line;
	string subStr;
	for (int i = 0; i < 4; i++)
	{
		getline(stepsFile, line);
		subStr = line.substr(9, 13);
		convertInputToDirection(subStr);
		ghost[i].setDirection(direction);
	}
}
void LoadMode::setFruitDirectionFromFile()
{
	string line;
	string subStr;

	getline(stepsFile, line);
	subStr = line.substr(7, 11);
	convertInputToDirection(subStr);
	fruit.setDirection(direction);

	//handles the case when the fruit born
	subStr = line.substr(12);
	if (!subStr.starts_with('\n'))
	{
		subStr = line.substr(13, 14);
		int xPos = stoi(subStr);
		subStr = line.substr(16, 17);
		int yPos = stoi(subStr);
		fruit.setCurrPos(xPos, yPos);
		subStr = line.substr(22);
		fruit.setFruitVal(stoi(subStr));
	}
}

void LoadMode::comparestepsToResultFile(int indexInFile)
{
	int numOfStepsInFile;

	string line;
	string subStr;

	getline(resultFile, line);
	subStr = line.substr(22);

	numOfStepsInFile = stoi(subStr);

	if (numOfStepsInFile == stepsCounter)
		testPassed = true;
	else
		testPassed = false;
}

void LoadMode::printAfterTest()
{
	clearScreen();
	if (testPassed)
		cout << "Test passed" << endl;
	else
		cout << "Test failed" << endl;

}


void LoadMode::convertInputToDirection(string _dir)
{

	if (_dir == "UP   ")
		direction = Direction::UP;

	else if (_dir == "DOWN ")
		direction = Direction::DOWN;

	else if (_dir == "LEFT ")
		direction = Direction::LEFT;

	else if (_dir == "RIGHT")
		direction = Direction::RIGHT;

	else
		direction = Direction::STAY;

}

