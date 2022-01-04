#pragma once

#include "SimpleMode.h"
#include <cstdio>
#include <fstream>

using std::ofstream;

class SaveMode : public SimpleMode
{
	string dir;
	int countsteps = 0;
	ofstream stepsFile;
	ofstream resultFile;

public:

	virtual void run() override;
	/*virtual void runAllSessions() override;
	virtual void runSingleScreensSession() override;
	virtual void runSingleScreen() override;*/
	void resetStepsCounter() { countsteps = 0; }
	void openFilesForWriting();
	void convertDirToInput(Direction _dir);
	void writeMovesToStepsFile();
	virtual void runGame() override;
	//void writeGhostDirToStepsFile(string input);
	//void writeFruitDirToStepsFile(string input);

	void writeLivesLeftToResultFile();
	void writeToResultFileEndOfSession();
	void writeToResultFileDuringSession();
	void writeToResultFileInvalidBoard();
	void removeOldFiles();
	void closeFiles();

};
