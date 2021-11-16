#pragma once
using namespace std;

#include "Utilities.h"
#include "Position.h"
#include <iostream>
#include <cstdlib>
#include <time.h>


class Position; //Forward declaration.

const int ROWMAX = 25;
const int COLMAX = 80;

class GameBoard
{
private:
	char _board[ROWMAX][COLMAX];
	int totalBreadcrumbs = 0;
	gameColors borderColor = WHITE; 
	gameColors breadcrumbColor = WHITE;
	gameColors tunnelColor = WHITE;

public:

	void initBoard();
	void initOuterBorders();
	void initInnerWalls();
	void initBreadcrumbs();
	void printBoard();

	void setBorderColor(gameColors color) { borderColor = color; }
	void setBreadcrumbColor(gameColors color) { breadcrumbColor = color; }
	void settunnelColor(gameColors color) { tunnelColor = color; }
	gameColors getBorderColor() { return borderColor; }
	gameColors getBreadcrumbColor() { return breadcrumbColor; }
	gameColors getTunnelColor() { return tunnelColor; }

	int getBreadcrumbs() { return totalBreadcrumbs - 1000; }
	void setCellInBoard(int& x, int& y, char ch) { _board[y][x] = ch; }
	void setCellInBoard(Position& pos, char ch);
	char getCellInBoard(int x, int y) { return _board[y][x]; }
	char getCellInBoard(Position& pos) const;
};