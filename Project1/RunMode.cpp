#include "ThePacmanGame.h"
#include "RunMode.h"
#include "LoadMode.h"
#include "SimpleMode.h"
#include "SilentMode.h"
#include "SaveMode.h"


RunMode::~RunMode()
{
	delete game;
}

void RunMode::assignGameModeAndRun()
{
	delete game;
	/*
	if (input.cmdOptionExists("-load"))
	{
		/*if (input.cmdOptionExists("-silent"))
			game = new SilentMode;
		//else
		game = new LoadMode;
	}
	else if (input.cmdOptionExists("-save"))
		game = new SaveMode;
	else
		game = new SimpleMode;
	*/
	game = new SimpleMode;
	game->run();
}

