#pragma once

#include "Utilities.h"
#include "Position.h"


class Menu
{

public:
	enum Diffculty { BEGINNER = 49, AMATEUR, PROFESSIONAL, EXTREME };
	static constexpr char START = '1', STARTCOLORIZED = '2', INSTRUCTIONS = '8', EXIT = '9', ESC = 27;
private:
	char userKey;
	Position legendAreaPos;
	Colors detailsColor = Colors::WHITE;
	int totalPlayerScore = 0;

public:
	char getUserKey() const { return userKey; }
	void setDetailsColor(Colors _detailsColor) { detailsColor = _detailsColor; }
	void pressAnyKey();
	void entryMenu();
	void printMenu() const;
	void printInstructions();
	void printDataAfterLosing(GameBoard& board, int& currTemplate) const;
	int getFirstBoardChoice(GameBoard& board);
	void printBoardsSelectionMenu(GameBoard& board, size_t& numOfTemplates) const;
	bool userChoosedToStart() const;
	bool userChoosedBoard(size_t& boardTemplatesSize) const;
	bool userChoosedDifficulty() const;
	void initDetailsArea(GameBoard& board);
	void setLegendAreaChars(GameBoard& board);
	void pauseGame(int lives) const;
	int getGameDifficulty();
	void printLevelsMenu();
	void updateTotalPlayerScore(int _totalPlayerScore) { totalPlayerScore = _totalPlayerScore; }

	void clearLegendArea() const;
	void betweenSessionsProcedure(GameBoard& board, int currTemplate, int lastGamePacmanScore, bool playerWon);
	void printDataAfterSession(GameBoard& board, int& currTemplate) const;
	void printAllLegend(int score, int lives);
	void singlePrintScore(int score) const;
	void printLives(int lives) const;
	void printGameName() const;
	void printRSG() const;
	void printPacmanAllAround(Colors pacmanColor) const;
	void printGhostsAllAround(Colors ghostColor) const;
	void printResult(bool playerWon, int score, Colors pacmanColor, Colors ghostColor) const;
};
