#pragma once

#include "SilentMode.h"
using std::vector;
using std::ifstream;
using std::cin;
using std::cin;

class LoadMode : public SilentMode
{
	int currStepsFile = 0;
	int currResultFile = 0;
	ifstream stepsFile;
	ifstream resultFile;
	vector <string> stepsfilesArr;
	vector <string> resultfilesArr;

	Direction direction;
public:
	void loadAllStepsAndResultFiles();
	void openFilesForRead();
	void closeCurrFiles();
	void readInfoFromStepsFile();
	void convertInputToDirection(string _dir);
	int convertStrToNum(string numToConvert);
	void setPacDirectionFromFile();
	void setGhostsDirectionFromFile();
	void setFruitDirectionFromFile();

};