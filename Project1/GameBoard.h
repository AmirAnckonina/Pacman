#pragma once

#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

using std::ifstream;
namespace filesystem = std::filesystem;

class Position; //Forward declaration.

class GameBoard
{
public:
	static const int ROWMAX = 25;
	static const int COLMAX = 80;
	static constexpr char SPACE = ' ', BORDER = (char)219, BREADCRUMB = (char)249, TUNNEL = (char)176, LEGEND = '&';
	enum BoardLoadingErrorTypes { EMPTYFILE, TOOWIDE, TOOLONG, RETRIEVE, INVALIDCREATURES };

private:
	char board[ROWMAX][COLMAX];
	int firstRow = ROWMAX, lastRow = -1, firstCol = COLMAX, lastCol = -1; //The first row and col that border appear, in order to recognize tunnels.
	bool validBoard = true;
	vector <string> boardTemplates = {};
	vector <Position> validPosStorage = {};
	int currTemplate = 0;
	int totalBreadcrumbs = 0;
	Colors borderColor = Colors::WHITE;
	Colors breadcrumbColor = Colors::WHITE;
	Colors tunnelColor = Colors::WHITE;

public:
	~GameBoard();
	//Init functions
	void loadAllScreenTemplates();
	void readRawTemplate();
	void sortByFirstBoardChosen(int userChosenTemplate);
	char convertChar(const char& ch);
	void initInvisibleTunnels();
	void resetCurrTemplate() { currTemplate = 0; }
	bool isValidBoard() { return validBoard; }
	void handleFirstRow(ifstream& templateFile, char& tmpChar, int& colsCounter);

	void initBoard();
	void countTotalBreadcrumbs();
	void resetBoard();

	//Printing and colors design
	void printBoard() const;
	void boardColorizedProcedure(int rowInd, int colInd) const;
	void reduceNumOfBreadCrumbs() { totalBreadcrumbs--; }
	void printInvalidBoardError(int errorCode) const;
	void lexSort();
	Position collectStartingPos(char ch) const;
	int collectnumOfGhosts() const;
	bool inBoardDimensions(int& x, int& y) const;
	bool inBoardDimensions(Position& pos) const;

	//Others Get-Set functions.
	bool isBoardValid() { return validBoard; }
	const string& getScreenTemplateName(int templateInd)const;
	const Position& getSpecificValidPosOnBoard(int index)const { return validPosStorage[index]; };
	void setBreadCrumbsPosArr();
	void setBoardFrame(int _lastRow, int _lastCol);
	void setBorderColor(Colors color = Colors::WHITE) { borderColor = color; }
	void setBreadcrumbColor(Colors color) { breadcrumbColor = color; }
	void settunnelColor(Colors color) { tunnelColor = color; }
	void setCellInBoard(int& x, int& y, char ch) { board[y][x] = ch; }
	void setCellInBoard(const Position& pos, char ch);
	Colors getBorderColor() const { return borderColor; }
	Colors getBreadcrumbColor() const { return breadcrumbColor; }
	Colors getTunnelColor() const { return tunnelColor; }
	int getBreadcrumbs() const { return totalBreadcrumbs; }
	size_t getValidPosStorage() const;
	char getCellInBoard(int x, int y) const { return board[y][x]; }
	char getCellInBoard(const Position& pos) const;
	int getFirstRow() const { return firstRow; }
	int getFirstCol() const { return firstCol; }
	int getLastRow() const { return lastRow; }
	int getLastCol() const { return lastCol; }
	int getCurrTemplate() const { return currTemplate; }
	size_t getNumOfTemplates() const;

	void validNumOfCreaturesOnBoard();

};