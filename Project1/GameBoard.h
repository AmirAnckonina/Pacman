#pragma once

#include "Utilities.h"
#include "Position.h"

using std::cout;
using std::endl;

class Position; //Forward declaration.


class GameBoard
{
public: 
	static const int ROWMAX = 25;
	static const int COLMAX = 80;
	static constexpr char SPACE = ' ', BORDER = 219, BREADCRUMB = 249, TUNNEL = 176;

private:
	char _board[ROWMAX][COLMAX];
	int totalBreadcrumbs = 0;
	bool boardColorized = false;
	Colors borderColor = Colors::WHITE;
	Colors breadcrumbColor = Colors::WHITE;
	Colors tunnelColor = Colors::WHITE;

public:

	void initBoard();
	void initOuterBorders();
	void initInnerWalls();
	void initBreadcrumbs();
	void initDetailsArea();
	void printBoard() const;
	void setBoardColorized() { boardColorized = true; }
	void setBorderColor(Colors color = Colors::WHITE) { borderColor = color; }
	void setBreadcrumbColor(Colors color) { breadcrumbColor = color; }
	void settunnelColor(Colors color) { tunnelColor = color; }
	void setCellInBoard(int& x, int& y, char ch) { _board[y][x] = ch; }
	void setCellInBoard(Position& pos, char ch) ;

	Colors getBorderColor() const { return borderColor; }
	Colors getBreadcrumbColor() const { return breadcrumbColor; }
	Colors getTunnelColor() const { return tunnelColor; }
	void boardColorizedProcedure(int rowInd, int colInd) const;
	int getBreadcrumbs() const { return totalBreadcrumbs; }
	char getCellInBoard(int x, int y) const { return _board[y][x]; }
	char getCellInBoard(Position& pos) const;

	};