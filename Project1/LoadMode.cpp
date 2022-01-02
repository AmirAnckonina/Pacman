#include "LoadMode.h"

void LoadMode::run()
{
	cout << "Hey, LoadMode" << endl;
	Sleep(2000);
	clearScreen();
	runAllSessions();
}

void LoadMode::runGame()
{

	return;
}

void LoadMode::singleFruitSession()
{
	return;
}

void LoadMode::executeSleepBetweenSessions()
{
	Sleep(20);
}
