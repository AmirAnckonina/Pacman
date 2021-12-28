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



public:
	char getUserKey() const { return userKey; }

	void pressAnyKey();
	void entryMenu();
	void printMenu() const;
	void printInstructions();

	int getFirstBoardChoice(GameBoard& board);
	void printBoardsSelectionMenu(GameBoard& board, size_t& numOfTemplates) const;
	bool userChoosedToStart() const;
	bool userChoosedBoard(size_t& boardTemplatesSize) const;
	bool userChoosedDifficulty() const;


	int getGameDifficulty();
	void printLevelsMenu();
};
