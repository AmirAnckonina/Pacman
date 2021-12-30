#include "LoadMode.h"

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
	//for pacman
	getline(stepsFile, line);
	line.substr(8, 12);
	convertInputToDirection(line);
	pacman.setDirection(direction);

	for (int i = 0; i < 4; i++)
	{
		getline(stepsFile, line);
		line.substr(9, 13);
		convertInputToDirection(line);
		ghost[i].setDirection(direction);
	}


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

