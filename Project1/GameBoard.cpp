#include "GameBoard.h"
#include "ThePacmanGame.h" 


void GameBoard::readTemplateFromFile()
{
	//getfilesFromDir();
	ifstream templateFile(boardTemplates[currTemplate + 2], ios::in);
	//Condiotion
	readRawTemplate(templateFile);
}

void GameBoard::readRawTemplate(ifstream& templateFile)
{
	int rowInd = 0, colInd = 0;
	char tmpChar;

	templateFile.get(tmpChar);
	while (tmpChar != EOF) //&& rowInd < ROWMAX)
	{
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
}


char GameBoard::convertChar(const char& ch)
{
	switch (ch)
	{
	case '#':
		return BORDER;
		break;
	case '%':
		//case '&':
		return SPACE;
		break;
	case ' ':
		return BREADCRUMB;
		break;
	default: //ch == 0, check waht happens with pacman and ghost icons
		break;
	}
}

void GameBoard::getfilesFromDir()
{
	string path;

	for (const auto& file : filesystem::directory_iterator("."))
	{
		if (file.path().extension() == ".screen")
		{
			path = file.path().string();
			path.erase(0, 2);
			boardTemplates.push_back(file.path().string());
		}
	}
	std::sort(boardTemplates.begin(), boardTemplates.end());
}

void GameBoard::initInvisibleTunnels()
{
	int rowInd = 0, colInd = 0;

	for (colInd = firstCol; colInd < lastCol; colInd++)
	{
		if (board[firstRow][colInd] == BREADCRUMB)
		{
			board[firstRow][colInd] = TUNNEL;
		}
	}

	for (rowInd = firstRow; rowInd < lastRow; rowInd++)
	{
		if (board[rowInd][firstCol] == BREADCRUMB)
		{
			board[rowInd][firstCol] = TUNNEL;
		}
	}

	for (colInd = firstCol; colInd < lastCol; colInd++)
	{
		if (board[lastRow][colInd] == BREADCRUMB)
		{
			board[lastRow][colInd] = TUNNEL;
		}
	}

	for (rowInd = firstRow; rowInd < lastRow; rowInd++)
	{
		if (board[rowInd][lastCol] == BREADCRUMB)
		{
			board[rowInd][lastCol] = TUNNEL;
		}
	}

}

void GameBoard::getBoardFrame()
{
	int rowInd, colInd;
	bool breakFlag = false;

	firstCol = COLMAX;
	firstRow = ROWMAX;
	lastRow = lastCol = -1;

	for (rowInd = 0; rowInd < ROWMAX; rowInd++)
		for (colInd = 0; colInd < COLMAX && colInd < firstCol; colInd++)
			if (board[rowInd][colInd] == BORDER && colInd < firstCol)
				firstCol = colInd;

	for (colInd = 0; colInd < COLMAX; colInd++)
		for (rowInd = 0; rowInd < ROWMAX && rowInd < firstRow; rowInd++)
			if (board[rowInd][colInd] == BORDER && rowInd < firstRow)
				firstRow = rowInd;

	for (rowInd = ROWMAX - 1; rowInd >= 0; rowInd--)
		for (colInd = COLMAX - 1; colInd >= 0 && colInd > lastCol; colInd--)
			if (board[rowInd][colInd] == BORDER && colInd > lastCol)
				lastCol = colInd;

	for (colInd = COLMAX - 1; colInd >= 0; colInd--)
		for (rowInd = ROWMAX - 1; rowInd >= 0 && rowInd > lastRow; rowInd--)
			if (board[rowInd][colInd] == BORDER && rowInd > lastRow)
				lastRow = rowInd;

}

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
	getBoardFrame();
	initInvisibleTunnels();
	countTotalBreadcrumbs();
	//printBoard();
}

void::GameBoard::initDetailsArea()
{
	int rowInd, colInd;
	for (rowInd = 11; rowInd <= 13; rowInd++)
		for (colInd = 21; colInd <= 59; colInd++)
			board[rowInd][colInd] = SPACE;
}

void GameBoard::initOuterBorders()
{
	int rowInd, colInd;

	for (rowInd = 0; rowInd < ROWMAX; rowInd++)
		board[rowInd][0] = BORDER;

	for (colInd = 0; colInd < COLMAX; colInd++)
		board[0][colInd] = BORDER;

	for (rowInd = 1; rowInd < ROWMAX; rowInd++)
		board[rowInd][COLMAX - 1] = BORDER;

	for (colInd = 0; colInd < COLMAX; colInd++)
		board[ROWMAX - 1][colInd] = BORDER;

	for (rowInd = 1; rowInd < ROWMAX - 1; rowInd++)
		for (colInd = 1; colInd < COLMAX - 1; colInd++)
			board[rowInd][colInd] = SPACE;

}

void GameBoard::initInnerWalls()
{
	int rowInd, colInd;

	//Tunnels
	for (rowInd = 10, colInd = 0; colInd <= 8; colInd++)
		board[rowInd][colInd] = BORDER;
	for (rowInd = 14, colInd = 0; colInd <= 8; colInd++)
		board[rowInd][colInd] = BORDER;
	for (rowInd = 10, colInd = 72; colInd <= 79; colInd++)
		board[rowInd][colInd] = BORDER;
	for (rowInd = 14, colInd = 72; colInd <= 79; colInd++)
		board[rowInd][colInd] = BORDER;
	for (rowInd = 11; rowInd <= 13; rowInd++)
	{
		board[rowInd][0] = TUNNEL;
		board[rowInd][COLMAX - 1] = TUNNEL;
	}


	//Big rectangle in the middle
	for (rowInd = 10; rowInd <= 14; rowInd++)
		for (colInd = 20; colInd <= 60; colInd++)
			board[rowInd][colInd] = BORDER;

	// Long lines
	for (rowInd = 17, colInd = 6; colInd <= 30; colInd++)
		board[rowInd][colInd] = BORDER;

	for (rowInd = 17, colInd = 50; colInd <= 74; colInd++)
		board[rowInd][colInd] = BORDER;

	for (rowInd = 7, colInd = 6; colInd <= 30; colInd++)
		board[rowInd][colInd] = BORDER;

	for (rowInd = 7, colInd = 50; colInd <= 74; colInd++)
		board[rowInd][colInd] = BORDER;

	//Short Lines
	for (rowInd = 10; rowInd <= 14; rowInd++)
		for (colInd = 19; colInd >= 11; colInd--)
			board[rowInd][colInd] = BORDER;
	for (rowInd = 10; rowInd <= 14; rowInd++)
		for (colInd = 61; colInd <= 69; colInd++)
			board[rowInd][colInd] = BORDER;

	//Small recatngles
	for (rowInd = 2; rowInd <= 7; rowInd++)
		for (colInd = 34; colInd <= 46; colInd++)
			board[rowInd][colInd] = BORDER;
	for (rowInd = 22; rowInd >= 17; rowInd--)
		for (colInd = 34; colInd <= 46; colInd++)
			board[rowInd][colInd] = BORDER;

	//4 Rectangles
	for (rowInd = 2; rowInd <= 7; rowInd++)
		for (colInd = 2; colInd <= 30; colInd++)
			board[rowInd][colInd] = BORDER;
	for (rowInd = 2; rowInd <= 7; rowInd++)
		for (colInd = 77; colInd >= 50; colInd--)
			board[rowInd][colInd] = BORDER;
	for (rowInd = 17; rowInd <= 22; rowInd++)
		for (colInd = 2; colInd <= 30; colInd++)
			board[rowInd][colInd] = BORDER;
	for (rowInd = 17; rowInd <= 22; rowInd++)
		for (colInd = 77; colInd >= 50; colInd--)
			board[rowInd][colInd] = BORDER;
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

void GameBoard::setCellInBoard(const Position& pos, char ch)
{
	board[pos.getYPos()][pos.getXPos()] = ch;
}

char GameBoard::getCellInBoard(const Position& pos) const
{
	return board[pos.getYPos()][pos.getXPos()];
}

Position GameBoard::collectStartingPos(char ch)
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

int GameBoard::collectnumOfGhosts()
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

