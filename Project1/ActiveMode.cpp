#pragma once


#include "ActiveMode.h"

void ActiveMode::openFilesForWriting()
{
	string stepsFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".steps";
	string resultFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".result";
	resultFile.open(resultFileName);
	stepsFile.open(stepsFileName);
}


//void runAllSessions(ThePacmanGame& game)
//{
//	hideCursor(); //
//	init_srand();
//
//	game.setActivation() = true;
//	size_t totalNumOfScreens;
//
//	game.getGameBoard().loadAllScreenTemplates();
//	totalNumOfScreens = getGameBoard().getNumOfTemplates();
//	game.getMenu().entryMenu();
//
//	while (game.isActive())
//	{
//		if (game.getMenu().getUserKey() == Menu::STARTCOLORIZED)
//			game.setGameColorized() = true;
//
//		if (game.getMenu().getUserKey() == Menu::EXIT)
//			game.setActivation = false;
//
//		if (game.isActive())
//		{
//			runSingleSession(totalNumOfScreens);
//			resetThePacmanGame();
//		}
//
//	}
//	clearScreen();
//	gotoxy(0, 0);
//	cout << "Goodbye" << endl;
//}

