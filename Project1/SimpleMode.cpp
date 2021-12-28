//#pragma once
//
//#include "SimpleMode.h"
//#include "ThePacmanGame.h"
//
//void SimpleMode::openFilesForWriting()
//{
//	string stepsFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".steps";
//	string resultFileName = game_board.getScreenTemplateName(game_board.getCurrTemplate()).substr(0, (game_board.getScreenTemplateName(game_board.getCurrTemplate()).size() - 6)) + ".result";
//	resultFile.open(resultFileName);
//	stepsFile.open(stepsFileName);
//}
//
//
//void SimpleMode::runAllSessions()
//{
//	hideCursor(); //
//	init_srand();
//
//	activate = true;
//	size_t totalNumOfScreens;
//	game_board.loadAllScreenTemplates();
//	totalNumOfScreens = game_board.getNumOfTemplates();
//	game_menu.entryMenu();
//
//	while (activate)
//	{
//		if (game_menu.getUserKey() == Menu::STARTCOLORIZED)
//			gameColorized = true;
//
//		if (game_menu.getUserKey() == Menu::EXIT)
//			activate = false;
//
//		if (activate)
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
//
//
//void SimpleMode::runSingleSession(size_t& totalNumOfScreens)
//{
//	
//	bool shouldEndSession = false;
//	int userChosenTemplate = game_menu.getFirstBoardChoice(game_board);
//	game_board.sortByFirstBoardChosen(userChosenTemplate);
//
//	for (int templateInd = 0; templateInd < totalNumOfScreens && !shouldEndSession && activate ; templateInd++)
//	{
//		if (game_menu.getUserKey() == Menu::EXIT)
//			activate = false;
//		else
//		{
//			if (game_menu.getUserKey() == Menu::STARTCOLORIZED)
//				gameColorized = true;
//
//			level = game_menu.getGameDifficulty();
//			initGame();
//			if (game_board.isValidBoard())
//			{
//				runGame();
//				if (pacman.getLivesLeft() == 0)
//					shouldEndSession = true;
//
//			}
//			game_menu.betweenSessionsProcedure(game_board, templateInd, pacman.getScore(), playerWon);
//			game_menu.entryMenu();
//		}
//	}
//}
//
//void SimpleMode::initSimpleModeGame()
//{
//	hideCursor();
//	init_srand();
//	initGame(level);
//
//	//game_menu.initDetailsArea(game_board); //Simple only
//	if (gameColorized) setGameColors();
//	else game_menu.setDetailsColor(Colors::WHITE);
//
//	printStart();
//
//}
//
//void SimpleMode::printStart()
//{
//	game_board.printBoard();
//	pacman.printCreature();
//	game_menu.printAllLegend(pacman.getScore(), pacman.getLivesLeft());
//	printAllGhosts();
//}
//
//void SimpleMode::resetThePacmanGame()
//{
//	pacman.resetScoreAndLives();
//	game_board.lexSort();
//	game_board.resetCurrTemplate();
//	playerWon = false;
//}
//
////Running a game session, according to do-while loop condition
//void SimpleMode::runGame()
//{
//	char key = 0;
//	Direction currDir;
//	do
//	{
//		if (key == Menu::ESC)
//		{
//			game_shell.pauseGame(pacman.getLivesLeft());
//			key = 0; //So pacman will continue as he was before pausing.
//		}
//		singleGhostsSession();
//		singlePacmanSession();
//		singleFruitSession();
//		printFigures();
//		Sleep(120);
//
//		if (_kbhit())
//		{
//			key = _getch(); //
//			currDir = pacman.convertKeyToDirection(key); //A kind of key translation to move.
//			if (currDir != Direction::WRONG_KEY)
//				pacman.setDirection(currDir);
//		}
//
//	} while (!GameFinished());
//
//	game_menu.printResult(playerWon, pacman.getScore(), pacman.getColor(), ghost[0].getColor());
//	if (gameColorized) { resetColors(); }
//	gameColorized = false;
//	clearScreen();
//	Sleep(1200);
//}
//
//
//void ThePacmanGame::singleFruitSession()
//{
//	if (fruit.isActive())
//	{
//		if (fruit.getTimeOnBoard() == 40)
//		{
//			fruit.generateLocation(game_board);
//			fruit.generateFruitValue();
//			fruit.ReduceTimeOnBoard();
//		}
//
//
//		if (fruitTurn)
//		{
//			fruit.move(game_board);
//			//afterMoveProcedure();
//			fruit.updatePos();
//			fruit.ReduceTimeOnBoard();
//			fruitTurn = false; //it won't move in the next step
//		}
//		else
//			fruitTurn = true;
//
//
//		if (isFruitEatenByPacman() || isFruitEatenByGhost())
//			fruitEatenProcedure();//when it becomes 
//
//		fruit.printCreature();
//
//		if (fruit.getTimeOnBoard() == 0)
//		{
//			fruit.disableActivity();
//			generalCellRestore(fruit);
//		}
//	}
//	else
//	{
//		fruit.ReduceTimeOffBoard();
//		if (fruit.getTimeOffBoard() == 0)
//			fruit.enableActivity();
//	}
//}
//
//
//void SimpleMode::fruitEatenProcedure()
//{
//	generalCellRestore(fruit);
//	fruit.disableActivity();
//	fruitTurn = true;
//}
//
//
//
////---------------------------------------------------------------//
//// 
//// 
//// 
//// 
//// 
//// 
//// 
////void runAllSessions(ThePacmanGame& game)
////{
////	hideCursor(); //
////	init_srand();
////
////	game.setActivation() = true;
////	size_t totalNumOfScreens;
////
////	game.getGameBoard().loadAllScreenTemplates();
////	totalNumOfScreens = getGameBoard().getNumOfTemplates();
////	game.getMenu().entryMenu();
////
////	while (game.isActive())
////	{
////		if (game.getMenu().getUserKey() == Menu::STARTCOLORIZED)
////			game.setGameColorized() = true;
////
////		if (game.getMenu().getUserKey() == Menu::EXIT)
////			game.setActivation = false;
////
////		if (game.isActive())
////		{
////			runSingleSession(totalNumOfScreens);
////			resetThePacmanGame();
////		}
////
////	}
////	clearScreen();
////	gotoxy(0, 0);
////	cout << "Goodbye" << endl;
////}
//
