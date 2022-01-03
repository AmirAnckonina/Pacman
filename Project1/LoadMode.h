#pragma once

#include "SilentMode.h"
using std::vector;
using std::ifstream;
using std::cin;


class LoadMode : public SilentMode
{
	
public:
	virtual void run() override;
	virtual void executeSleepBetweenSessions() override;
//	virtual void runAllSessions() override;
//	virtual void runSingleScreensSession() override;
//	virtual void runGame() override;
//	virtual void singleFruitSession() override;
//
//	void loadAllStepsAndResultFiles();
//	void openFilesForRead();
//	void closeCurrFiles();
//	void readInfoFromStepsFile();
//	void convertInputToDirection(string _dir);
//	int convertStrToNum(string numToConvert);
//	void setPacDirectionFromFile();
//	void setGhostsDirectionFromFile();
//	void setFruitDirectionFromFile();
//	void comparestepsToResultFile(int indexInFile);
//	void printAfterTest();

};