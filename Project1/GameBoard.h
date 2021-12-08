#pragma once
using namespace std;

#include "Utilities.h"
#include "Position.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


class Position; //Forward declaration.
class GameBoard
{
public:
	static const int ROWMAX = 25;
	static const int COLMAX = 80;
	static constexpr char SPACE = ' ', BORDER = 219, BREADCRUMB = 249, TUNNEL = 176, LEGEND = '&';

private:
	char board[ROWMAX][COLMAX];
	//The first row and col that border appear, in order to recognize tunnels.
	int firstRow = ROWMAX, lastRow = -1, firstCol = COLMAX, lastCol = -1;
	string boardTemplates[5] = { "Pacman_board_1.txt", "Pacman_board_2.txt", "Pacman_board_3.txt",
		"Pacman_board_4.txt", "Pacman_board_5.txt" };
	int currTemplate = 0;
	int totalBreadcrumbs = 0;
	bool boardColorized = false;
	Colors borderColor = Colors::WHITE;
	Colors breadcrumbColor = Colors::WHITE;
	Colors tunnelColor = Colors::WHITE;

public:

	//Init functions
	void readTemplateFromFile();
	void readRawTemplate(ifstream& templateFile);
	char convertChar(const char& ch);
	void initInvisibleTunnels();
	void getBoardFrame();
	//long int fileSize(ifstream& fp);

	void initBoard();
	void initOuterBorders();
	void initInnerWalls();
	void countTotalBreadcrumbs();
	void initDetailsArea();
	void resetBoard();

	//Printing and colors design
	void printBoard() const;
	void setBoardColorized() { boardColorized = true; }
	void setBorderColor(Colors color = Colors::WHITE) { borderColor = color; }
	void setBreadcrumbColor(Colors color) { breadcrumbColor = color; }
	void settunnelColor(Colors color) { tunnelColor = color; }
	void boardColorizedProcedure(int rowInd, int colInd) const;

	//Others Get-Set functions.
	void setCellInBoard(int& x, int& y, char ch) { board[y][x] = ch; }
	void setCellInBoard(const Position& pos, char ch);
	Colors getBorderColor() const { return borderColor; }
	Colors getBreadcrumbColor() const { return breadcrumbColor; }
	Colors getTunnelColor() const { return tunnelColor; }
	int getBreadcrumbs() const { return totalBreadcrumbs; }
	char getCellInBoard(int x, int y) const { return board[y][x]; }
	char getCellInBoard(const Position& pos) const;

	int getFirstRow() { return firstRow; }
	int getFirstCol() { return firstCol; }
	int getLastRow() { return lastRow; }
	int getLastCol() { return lastCol; }

	Position collectStartingPos(char ch);
};