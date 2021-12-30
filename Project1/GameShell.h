#pragma once


#include "Utilities.h"
#include "Position.h"

class GameShell
{
	Position legendAreaPos;
	int totalPlayerScore = 0;
	Colors detailsColor = Colors::WHITE;


public:
	void setDetailsColor(Colors _detailsColor) { detailsColor = _detailsColor; }
	void printDataAfterLosing(GameBoard& board, int& currTemplate) const;
	void initDetailsArea(GameBoard& board);
	void setLegendAreaChars(GameBoard& board);
	void updateTotalPlayerScore(int _totalPlayerScore) { totalPlayerScore = _totalPlayerScore; }
	void clearLegendArea() const;
	void betweenScreensProcedure(GameBoard& board, int currTemplate, int lastGamePacmanScore, bool playerWon);
	void printDataAfterSession(GameBoard& board, int& currTemplate) const;
	void printAllLegend(int score, int lives) const;
	void singlePrintScore(int score) const;
	void printLives(int lives) const;
	void printGameName() const;
	void printRSG() const;
	void printPacmanAllAround(Colors pacmanColor) const;
	void printGhostsAllAround(Colors ghostColor) const;
	void printResult(bool playerWon, int score, Colors pacmanColor, Colors ghostColor) const;
	void pauseGame(int lives) const;

};

