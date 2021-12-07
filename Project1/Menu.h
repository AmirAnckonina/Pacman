#pragma once

#include "Utilities.h"
#include "Position.h"

using std::cout;
using std::endl;

class Menu
{
public:
	static constexpr char START = '1', STARTCOLORIZED = '2', INSTRUCTIONS = '8', EXIT = '9', ESC = 27;

private:
	char userKey;
	
public:
	char getUserKey() const { return userKey; }
	void entryMenu();
	void printMenu() const;
	void printInstructions();
	bool userChoosedToStart() const ; 
};
