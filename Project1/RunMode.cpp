#include "ThePacmanGame.h"
#include "RunMode.h"
#include "LoadMode.h"
#include "SimpleMode.h"
#include "SilentMode.h"
#include "SaveMode.h"


void RunMode::assignGameModeAndRun(const char* _runModeType)
{
	/*if (strcmp(_runModeType, "load"))
	{
		game = new LoadMode;
	}
	else if (strcmp(_runModeType, "save"))
	{
		game = new SaveMode;
	}
	else if (strcmp(_runModeType, "silent"))
	{
		game = new SilentMode;
	}
	else
	{*/
		game = new SimpleMode;
	//}

	game->runAllSessions();
}

