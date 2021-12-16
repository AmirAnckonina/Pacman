#include "GameBoard.h"
#include "Position.h"
#include "ThePacmanGame.h" 


void GameBoard::readTemplateFromFile()
{
	ifstream templateFile(boardTemplates[currTemplate], std::ios::in);
	if (templateFile)
		readRawTemplate(templateFile);
	else
		return;
}

void GameBoard::readRawTemplate(ifstream& templateFile)
{
	int rowInd = 0, colInd = 0;
	char tmpChar;
	bool flag = false;

	tmpChar = templateFile.get();

	isEmptyFile(tmpChar);

	while (tmpChar != EOF) //&& rowInd < ROWMAX)
	{
		if (tmpChar == '\n' && flag == false)
		{
			
			flag = true;
		}
		if (flag == false)
			countCols++;

		if (tmpChar == '\n') //END_OF_LINE
		{
			rowInd++;
			colInd = 0;
		}
		else
		{
			tmpChar = convertChar(tmpChar);
			board[rowInd][colInd++] = tmpChar;
		}
		tmpChar = templateFile.get();
	}
	lastRow = rowInd;
	lastCol = countCols - 1;
	firstCol = 0;
	firstRow = 0;
}


bool GameBoard::isEmptyFile(char ch)
{
	if (ch == '\n')
		return false;
	return true;
}


char GameBoard::convertChar(const char& ch)
{
	switch (ch)
	{
	case '#':
		return BORDER;
	case '%':
		//case '&':
		return SPACE;
	case ' ':
		return BREADCRUMB;
	default: //ch == 0, check waht happens with pacman and ghost icons
		return ch;
	}
}

void GameBoard::loadAllScreenTemplates()
{
	string path;

	for (const auto& file : filesystem::directory_iterator("."))
	{
		if (file.path().string().ends_with(".screen"))
		{
			path = file.path().string();
			path.erase(0, 2);
			boardTemplates.push_back(path); //.path().string());
		}
	}
	std::sort(boardTemplates.begin(), boardTemplates.end());
}

void GameBoard::initInvisibleTunnels()
{
	int rowInd = 0, colInd = 0;

	for (colInd = firstCol; colInd <= lastCol; colInd++)
	{
		if (board[firstRow][colInd] == BREADCRUMB)
		{
			board[firstRow][colInd] = TUNNEL;
		}
	}

	for (rowInd = firstRow; rowInd <= lastRow; rowInd++)
	{
		if (board[rowInd][firstCol] == BREADCRUMB)
		{
			board[rowInd][firstCol] = TUNNEL;
		}
	}

	for (colInd = firstCol; colInd <= lastCol; colInd++)
	{
		if (board[lastRow][colInd] == BREADCRUMB)
		{
			board[lastRow][colInd] = TUNNEL;
		}
	}

	for (rowInd = firstRow; rowInd <= lastRow; rowInd++)
	{
		if (board[rowInd][lastCol] == BREADCRUMB)
		{
			board[rowInd][lastCol] = TUNNEL;
		}
	}

}

/*void GameBoard::getBoardFrame()
{
	int rowInd, colInd;
	bool breakFlag = false;

	firstCol = 0;
	firstRow = 0;
	//lastRow = lastCol = -1;
	//lastCol = countCols;
	countCols = 0;

	//for (rowInd = 0; rowInd < ROWMAX; rowInd++)
	//	for (colInd = 0; colInd < COLMAX && colInd < firstCol; colInd++)
	//		if (board[rowInd][colInd] == BORDER && colInd < firstCol)
	//			firstCol = colInd;
	//
	//for (colInd = 0; colInd < COLMAX; colInd++)
	//	for (rowInd = 0; rowInd < ROWMAX && rowInd < firstRow; rowInd++)
	//		if (board[rowInd][colInd] == BORDER && rowInd < firstRow)
	//			firstRow = rowInd;
	//
	//for (rowInd = ROWMAX - 1; rowInd >= 0; rowInd--)
	//	for (colInd = COLMAX - 1; colInd >= 0 && colInd > lastCol; colInd--)
	//		if (board[rowInd][colInd] == BORDER && colInd > lastCol)
	//			lastCol = colInd;
	//
	//for (colInd = COLMAX - 1; colInd >= 0; colInd--)
	//	for (rowInd = ROWMAX - 1; rowInd >= 0 && rowInd > lastRow; rowInd--)
	//		if (board[rowInd][colInd] == BORDER && rowInd > lastRow)
	//			lastRow = rowInd;

}*/

void GameBoard::countTotalBreadcrumbs()
{
	int rowInd, colInd;

	for (rowInd = 0; rowInd < ROWMAX; rowInd++)
	{
		for (colInd = 0; colInd < COLMAX; colInd++)
		{
			if (board[rowInd][colInd] == BREADCRUMB)
			{
				totalBreadcrumbs++;
			}
		}
	}
}

void GameBoard::resetBoard()
{
	int rowInd, colInd;
	for (rowInd = 0; rowInd < ROWMAX; rowInd++)
		for (colInd = 0; colInd < COLMAX; colInd++)
			board[rowInd][colInd] = SPACE;
}

void GameBoard::initBoard()
{
	borderColor = breadcrumbColor = tunnelColor = Colors::WHITE;
	boardColorized = false;
	totalBreadcrumbs = 0;

	resetBoard();
	readTemplateFromFile();
	//getBoardFrame();
	initInvisibleTunnels();
	countTotalBreadcrumbs();
	//printBoard();
}

void GameBoard::printBoard() const
{
	gotoxy(0, 0);
	int rowInd, colInd;
	for (rowInd = 0; rowInd < ROWMAX; rowInd++)
	{
		for (colInd = 0; colInd < COLMAX; colInd++)
		{
			if (ThePacmanGame::isGameColorized())
				boardColorizedProcedure(rowInd, colInd);
			cout << board[rowInd][colInd];
		}
		if (rowInd < ROWMAX - 1)
			cout << endl;
	}
}

void GameBoard::boardColorizedProcedure(int rowInd, int colInd) const
{
	if (board[rowInd][colInd] == BORDER)
		setTextColor(borderColor);
	else if (board[rowInd][colInd] == BREADCRUMB)
		setTextColor(breadcrumbColor);
	else //TUNNEL
		setTextColor(tunnelColor);
}

bool GameBoard::inBoardDimensions(int& x, int& y) const
{
	bool isXOk = false;
	bool isYOk = false;

	if (y >= firstRow && y <= lastRow)
		isYOk = true;
	if (x >= firstCol && x <= lastCol)
		isXOk = true;

	return isXOk && isYOk;
}

bool GameBoard::inBoardDimensions(Position& pos) const
{
	bool isXOk = false;
	bool isYOk = false;

	if (pos.getYPos() >= firstRow && pos.getYPos() <= lastRow)
		isYOk = true;
	if (pos.getXPos() >= firstCol && pos.getXPos() <= lastCol)
		isXOk = true;

	return isXOk && isYOk;
}

void GameBoard::setCellInBoard(const Position& pos, char ch)
{
	board[pos.getYPos()][pos.getXPos()] = ch;
}

char GameBoard::getCellInBoard(const Position& pos) const
{
	return board[pos.getYPos()][pos.getXPos()];
}

size_t GameBoard::getNumOfTemplates() const 
{
	return boardTemplates.size();
}

Position GameBoard::collectStartingPos(char ch) const
{
	Position res;
	for (int rowInd = 0; rowInd < ROWMAX; rowInd++)
	{
		for (int colInd = 0; colInd < COLMAX; colInd++)
		{
			if (getCellInBoard(colInd, rowInd) == ch)
			{
				res.setXPos(colInd);
				res.setYPos(rowInd);
				return res;
			}
		}
	}
	return NULL;
}

int GameBoard::collectnumOfGhosts() const
{
	int counter = 0;
	for (int i = firstRow; i < lastRow; i++)
	{
		for (int j = firstCol; j < lastCol; j++)
		{
			if (board[i][j] == Creature::GHOST)
				counter++;
		}
	}
	return counter;
}

