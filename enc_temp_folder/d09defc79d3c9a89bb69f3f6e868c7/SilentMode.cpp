#include "SilentMode.h"

#include "LoadMode.h"

void SilentMode::run()
{
	cout << "Running in Silent Mode" << endl;
	Sleep(2000);
	clearScreen();
	runAllSessions();
}

void SilentMode::runAllSessions()
{
	loadScreens();
	loadAllStepsAndResultFiles();
	runSingleScreensSession();
	goodBye();
}

void SilentMode::runSingleScreensSession()
{
	string currObj;
	//Typeid helper
	currObj = typeid(*this).name();
	currObj = currObj.substr(6);
	pacmanDied = false;

	for (currStepsFile = 0, currResultFile = 0; currStepsFile < stepsfilesArr.size() && !pacmanDied && activate; currStepsFile++, currResultFile++)
	{
		openFilesForRead();
		initSingleScreen();
		setAllCreaturesMoveStrategy();
		runSingleScreen();

		if (currObj == "LoadMode")
			game_shell.betweenScreensProcedure(game_board, currScreenInd, pacman.getScore(), playerWon);
	}
}

void SilentMode::runGame()
{
	string currObj;
	//Typeid helper
	currObj = typeid(*this).name();
	currObj = currObj.substr(6);

	do
	{
		stepsCounter++;
		readInfoFromStepsFile();

		if (currObj == "LoadMode") ThePacmanGame::singleCreaturesIteration();
		else singleCreaturesIteration();

		if (collisionInCurrStepIndicator) 
			comparestepsToResultFile();

	} while (!GameFinished() && testPassed);

	comparestepsToResultFile();
	printAfterTest();


	if (currObj == "LoadMode") afterRunGameProcedure();

	return;
}

void SilentMode::singleCreaturesIteration()
{
	singleGhostsSession();
	completeGhostsSession();
	singlePacmanSession();
	completePacmanSession();
	singleFruitSession();
}

void SilentMode::completeGhostsSession()
{
	if (isFruitEatenByGhost())
		fruit.disableActivity();

	if (checkCollision())
		collisionProcedure();
}

void SilentMode::completePacmanSession()
{
	if (isFruitEatenByPacman())
		fruit.disableActivity();

	if (!checkCollision())
		updateScoreAndBoardAfterPacman();
	else
		collisionProcedure();
}


void SilentMode::singleFruitSession()
{

	if (fruit.isActive())
	{
		//Only for Simple - Save


		if (fruitTurn)
		{
			//To all modes
			fruit.move(game_board);
			fruit.updatePrevPos();
			fruit.updatePos();
		}
		else
			fruitTurn = true;


		if (isFruitEatenByPacman() || isFruitEatenByGhost())
			fruit.disableActivity();


		if (fruit.getDirection() == Direction::STAY)
		{
			fruit.disableActivity();
		}

	}
	else
	{
		if (fruit.getTimeOffBoard() == 0)
			fruit.enableActivity();
	}
}

void SilentMode::setAllCreaturesMoveStrategy()
{
	pacman.setCreatureStrategyType(Creature::INPUT);
	pacman.setMoveStrategy();
	for (int i = 0; i < numOfGhosts; i++)
	{
		ghost[i].setCreatureStrategyType(Creature::INPUT);
		ghost[i].setMoveStrategy();
	}
	fruit.setCreatureStrategyType(Creature::INPUT);
	fruit.setMoveStrategy();
}

void SilentMode::loadAllStepsAndResultFiles()
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

void SilentMode::openFilesForRead()
{
	stepsFile.open(stepsfilesArr[currStepsFile]);
	resultFile.open(resultfilesArr[currResultFile]);
}

void SilentMode::closeCurrFiles()
{
	stepsFile.close();
	resultFile.close();
}

void SilentMode::readInfoFromStepsFile()
{
	setPacDirectionFromFile();
	setGhostsDirectionFromFile();
	setFruitDirectionFromFile();
}

int SilentMode::convertStrToNum(string numToConvert)
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

void SilentMode::setPacDirectionFromFile()
{
	string line;
	string subStr;
	getline(stepsFile, line);
	subStr = line.substr(8, 12);
	convertInputToDirection(subStr);
	pacman.setDirection(direction);
}

void SilentMode::setGhostsDirectionFromFile()
{
	string line;
	string subStr;
	for (int i = 0; i < numOfGhosts; i++)
	{
		getline(stepsFile, line);
		subStr = line.substr(8, 12);
		convertInputToDirection(subStr);
		ghost[i].setDirection(direction);
	}
}

void SilentMode::setFruitDirectionFromFile()
{
	string line;
	string subStr;

	getline(stepsFile, line);
	subStr = line.substr(7, 11);
	convertInputToDirection(subStr);
	fruit.setDirection(direction);

	//handles the case when the fruit born
	subStr = line.substr(11);
	//if (subStr[0] != '\0') //)//(!subStr.starts_with('\n'))
	if ( isdigit( line[line.length() - 1] ) )
	{
		subStr = line.substr(15, 16);
		int xPos = stoi(subStr);
		subStr = line.substr(18, 19);
		int yPos = stoi(subStr);
		fruit.setCurrPos(xPos, yPos);
		subStr = line.substr(24);
		fruit.setFruitVal(stoi(subStr));
	}
}

void SilentMode::comparestepsToResultFile()
{
	int numOfStepsInFile;

	string line;
	string subStr;

	getline(resultFile, line);
	size_t last_index = line.find_last_not_of("0123456789");
	subStr = line.substr(last_index + 1);

	numOfStepsInFile = stoi(subStr);

	if (numOfStepsInFile == stepsCounter)
		testPassed = true;
	else
		testPassed = false;
}

void SilentMode::printAfterTest()
{
	clearScreen();
	if (testPassed)
		cout << "Test passed" << endl;
	else
		cout << "Test failed" << endl;

	Sleep(2000);
}

void SilentMode::convertInputToDirection(string _dir)
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

//string str = "sdfsd34";
//size_t last_index = str.find_last_not_of("0123456789");
//string result = str.substr(last_index + 1);