#pragma once

#include "Utilities.h"
#include "Position.h"

using std::cout;
using std::endl;

class Position; //Forward declaration.

const int ROWMAX = 25;
const int COLMAX = 80;

class GameBoard
{
private:

	char _board[ROWMAX][COLMAX];
	int totalBreadcrumbs = 0;
	gameColors borderColor = gameColors::WHITE;
	gameColors breadcrumbColor = gameColors::WHITE;
	gameColors tunnelColor = gameColors::WHITE;

public:

	void initBoard();
	void initOuterBorders();
	void initInnerWalls();
	void initBreadcrumbs();
	void initDetailsArea();
	void printBoard();

	void setBorderColor(gameColors color = gameColors::WHITE) { borderColor = color; }
	void setBreadcrumbColor(gameColors color) { breadcrumbColor = color; }
	void settunnelColor(gameColors color) { tunnelColor = color; }
	gameColors getBorderColor() const { return borderColor; }
	gameColors getBreadcrumbColor() const { return breadcrumbColor; }
	gameColors getTunnelColor() const { return tunnelColor; }

	int getBreadcrumbs() const { return totalBreadcrumbs; }
	void setCellInBoard(int& x, int& y, char ch) { _board[y][x] = ch; }
	void setCellInBoard(Position& pos, char ch) ;
	char getCellInBoard(int x, int y) { return _board[y][x]; }
	char getCellInBoard(Position& pos) const;

	};