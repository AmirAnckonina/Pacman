#pragma once
using namespace std;

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Position.h"



const int ROWMAX = 25;
const int COLMAX = 80;
const char SPACE = ' ';
const char BORDER = 219;
const char BREADCRUMB = '*';

class Position; //Forward declaration.
class GameBoard
{
private:
	char _board[ROWMAX][COLMAX];
	int numOfbreadcrumbs = 0;
	//Color = ?

public:

	void initBoard();
	void initOuterBorders();
	void initInnerWalls();
	void initBreadcrumbs();
	void printBoard();
	int getBreadcrumbs() { return numOfbreadcrumbs; }
	void setCellInBoard(int& x, int& y, char ch) { _board[y][x] = ch; }
	void setCellInBoard(Position& pos, char ch);
	char getCellInBoard(int x, int y) { return _board[y][x]; }
	char getCellInBoard(Position& pos) const;

	//void printCellInBoard(Position& pos) const
	//{
	//	cout << _board[pos.getXPos()][pos.getYPos()];
	//}
};