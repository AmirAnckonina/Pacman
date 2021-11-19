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
	bool boardColorized = false;
	gameColors borderColor = gameColors::WHITE;
	gameColors breadcrumbColor = gameColors::WHITE;
	gameColors tunnelColor = gameColors::WHITE;

public:

	void initBoard();
	void initOuterBorders();
	void initInnerWalls();
	void initBreadcrumbs();
	void initDetailsArea();
	void printBoard() const;
	void setBoardColorized() { boardColorized = true; }
	void setBorderColor(gameColors color = gameColors::WHITE) { borderColor = color; }
	void setBreadcrumbColor(gameColors color) { breadcrumbColor = color; }
	void settunnelColor(gameColors color) { tunnelColor = color; }
	void setCellInBoard(int& x, int& y, char ch) { _board[y][x] = ch; }
	void setCellInBoard(Position& pos, char ch) ;

	gameColors getBorderColor() const { return borderColor; }
	gameColors getBreadcrumbColor() const { return breadcrumbColor; }
	gameColors getTunnelColor() const { return tunnelColor; }
	void boardColorizedProcedure(int rowInd, int colInd) const;
	int getBreadcrumbs() const { return totalBreadcrumbs; }
	char getCellInBoard(int x, int y) const { return _board[y][x]; }
	char getCellInBoard(Position& pos) const;

	};