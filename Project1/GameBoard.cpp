#include "GameBoard.h"
#include "ThePacmanGame.h" 


void GameBoard::readTemplateFromFile()
{
	ifstream templateFile(boardTemplates[currTemplate+2], ios::in);
	readRawTemplate(templateFile);
}

void GameBoard::readRawTemplate(ifstream& templateFile)
{
	int rowInd = 0, colInd = 0;
	char tmpChar;
	long int fsize = fileSize(templateFile);
	
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
			_board[rowInd][colInd++] = tmpChar;
		}
		tmpChar = templateFile.get();
	}
}

long int GameBoard::fileSize(ifstream& fp)
{
	long int res, saver;
	saver = fp.tellg();
	fp.seekg(ios::end);
	res = fp.tellg();
	fp.seekg(saver);
	cout << res << endl;
	return res;
}

char GameBoard::convertChar(const char& ch)
{
	switch (ch)
	{
	case '#':
		return BORDER;
		break;
	case '%':
	case '&':
		return SPACE;
		break;
	case ' ':
		return BREADCRUMB;
		break;
	default: //ch == 0
		return SPACE;
		break;
	}
}

void GameBoard::initInvisibleTunnels(int& firstRow, int& lastRow, int& firstCol, int& lastCol)
{
	int rowInd = 0, colInd = 0;

	for (rowInd = 0, colInd = 0; colInd < lastCol; colInd++)
	{
		if (_board[firstRow][colInd] == BREADCRUMB)
		{
			_board[firstRow][colInd] = TUNNEL;
		}
	}

	for (rowInd = 0, colInd = 0; rowInd < lastRow; rowInd++)
	{
		if (_board[rowInd][firstCol] == BREADCRUMB)
		{
			_board[rowInd][firstCol] = TUNNEL;
		}
	}
	
	for (rowInd = 0, colInd = 0; colInd < lastCol; colInd++)
	{
		if (_board[lastRow][colInd] == BREADCRUMB)
		{
			_board[lastRow][colInd] = TUNNEL;
		}
	}

	for (rowInd = 0, colInd = 0; rowInd < lastRow; rowInd++)
	{
		if (_board[rowInd][lastCol] == BREADCRUMB)
		{
			_board[rowInd][lastCol] = TUNNEL;
		}
	}

}

void GameBoard::initBoard()
{
	borderColor = breadcrumbColor = tunnelColor = Colors::WHITE;
	boardColorized = false;
	totalBreadcrumbs = 0;

	readTemplateFromFile();
	int firstRow, lastRow, firstCol, lastCol; //The first row and col that border appear, in order to recognize tunnels.
	getBoardFrame(firstRow, lastRow, firstCol, lastCol);
	initInvisibleTunnels(firstRow, lastRow, firstCol, lastCol);
	printBoard();
}

void GameBoard::getBoardFrame(int& firstRow, int& lastRow, int& firstCol, int& lastCol)
{
	int rowInd, colInd;
	bool breakFlag = false;

	firstCol = COLMAX;
	firstRow = ROWMAX;
	lastRow = lastCol = -1;

	for (rowInd = 0; rowInd < ROWMAX ; rowInd++)
		for (colInd = 0; colInd < COLMAX && colInd < firstCol ; colInd++)
			if (_board[rowInd][colInd] == BORDER && colInd < firstCol)
				firstCol = colInd;
	
	for (colInd = 0; colInd < COLMAX ; colInd++)
		for (rowInd = 0; rowInd < ROWMAX && rowInd < firstRow; rowInd++)
			if (_board[rowInd][colInd] == BORDER && rowInd < firstRow)
				firstRow = rowInd;

	for (rowInd = ROWMAX - 1 ; rowInd >= 0; rowInd--)
		for (colInd = COLMAX - 1 ; colInd >= 0 && colInd > lastCol ; colInd--)
			if (_board[rowInd][colInd] == BORDER && colInd > lastCol)
				lastCol = colInd;

	for (colInd = COLMAX - 1; colInd >= 0; colInd--)
		for (rowInd = ROWMAX - 1; rowInd >= 0 && rowInd > lastRow; rowInd--)
			if (_board[rowInd][colInd] == BORDER && rowInd > lastRow)
				lastRow = rowInd;

}

void::GameBoard::initDetailsArea()
{
	int rowInd, colInd;
	for (rowInd = 11; rowInd <= 13; rowInd++)
		for (colInd = 21; colInd <= 59; colInd++)
			_board[rowInd][colInd] = SPACE;
}

void GameBoard::initOuterBorders()
{
	int rowInd, colInd;

	for (rowInd = 0; rowInd < ROWMAX; rowInd++)
		_board[rowInd][0] = BORDER;

	for (colInd = 0; colInd < COLMAX; colInd++)
		_board[0][colInd] = BORDER;

	for (rowInd = 1; rowInd < ROWMAX; rowInd++)
		_board[rowInd][COLMAX - 1] = BORDER;

	for (colInd = 0; colInd < COLMAX; colInd++)
		_board[ROWMAX - 1][colInd] = BORDER;

	for (rowInd = 1; rowInd < ROWMAX - 1; rowInd++)
		for (colInd = 1; colInd < COLMAX - 1; colInd++)
			_board[rowInd][colInd] = SPACE;

}

void GameBoard::initInnerWalls()
{
	int rowInd, colInd;

	//Tunnels
	for (rowInd = 10, colInd = 0; colInd <= 8; colInd++)
		_board[rowInd][colInd] = BORDER;
	for (rowInd = 14, colInd = 0; colInd <= 8; colInd++)
		_board[rowInd][colInd] = BORDER;
	for (rowInd = 10, colInd = 72; colInd <= 79; colInd++)
		_board[rowInd][colInd] = BORDER;
	for (rowInd = 14, colInd = 72; colInd <= 79; colInd++)
		_board[rowInd][colInd] = BORDER;
	for (rowInd = 11; rowInd <= 13; rowInd++)
	{
		_board[rowInd][0] = TUNNEL;
		_board[rowInd][COLMAX - 1] = TUNNEL;
	}


	//Big rectangle in the middle
	for (rowInd = 10; rowInd <= 14; rowInd++)
		for (colInd = 20; colInd <= 60; colInd++)
			_board[rowInd][colInd] = BORDER;

	// Long lines
	for (rowInd = 17, colInd = 6; colInd <= 30; colInd++)
		_board[rowInd][colInd] = BORDER;

	for (rowInd = 17, colInd = 50; colInd <= 74; colInd++)
		_board[rowInd][colInd] = BORDER;

	for (rowInd = 7, colInd = 6; colInd <= 30; colInd++)
		_board[rowInd][colInd] = BORDER;

	for (rowInd = 7, colInd = 50; colInd <= 74; colInd++)
		_board[rowInd][colInd] = BORDER;

	//Short Lines
	for (rowInd = 10 ; rowInd <= 14 ; rowInd++)
		for (colInd = 19; colInd >= 11; colInd--)
			_board[rowInd][colInd] = BORDER;
	for (rowInd = 10; rowInd <= 14; rowInd++)
		for (colInd = 61; colInd <= 69; colInd++)
			_board[rowInd][colInd] = BORDER;

	//Small recatngles
	for (rowInd = 2; rowInd <= 7; rowInd++)
		for (colInd = 34; colInd <= 46; colInd++)
			_board[rowInd][colInd] = BORDER;
	for (rowInd = 22; rowInd >= 17; rowInd--)
		for (colInd = 34; colInd <= 46; colInd++)
			_board[rowInd][colInd] = BORDER;

	//4 Rectangles
	for (rowInd = 2; rowInd <= 7; rowInd++)
		for (colInd = 2; colInd <= 30; colInd++)
			_board[rowInd][colInd] = BORDER;
	for (rowInd = 2; rowInd <= 7; rowInd++)
		for (colInd = 77; colInd >= 50; colInd--)
			_board[rowInd][colInd] = BORDER;
	for (rowInd = 17; rowInd <= 22; rowInd++)
		for (colInd = 2; colInd <= 30; colInd++)
			_board[rowInd][colInd] = BORDER;
	for (rowInd = 17; rowInd <= 22; rowInd++)
		for (colInd = 77; colInd >= 50; colInd--)
			_board[rowInd][colInd] = BORDER;
}

void GameBoard::initBreadcrumbs()
{
	int rowInd, colInd;

	for (rowInd = 0; rowInd < ROWMAX; rowInd++)
	{
		for (colInd = 0; colInd < COLMAX; colInd++)
		{
			if (_board[rowInd][colInd] == SPACE)
			{
				_board[rowInd][colInd] = BREADCRUMB;
				totalBreadcrumbs++;
			}
		}
	}
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
			cout << _board[rowInd][colInd];
		}
		if (rowInd < ROWMAX - 1)
			cout << endl;
	}
}

void GameBoard::boardColorizedProcedure(int rowInd, int colInd) const
{
	if (_board[rowInd][colInd] == BORDER)
		setTextColor(borderColor);
	else if (_board[rowInd][colInd] == BREADCRUMB)
		setTextColor(breadcrumbColor);
	else //TUNNEL
		setTextColor(tunnelColor);
}

void GameBoard::setCellInBoard(Position& pos, char ch)
{
	_board[pos.getYPos()][pos.getXPos()] = ch;
}

char GameBoard::getCellInBoard(Position& pos) const
{
	return _board[pos.getYPos()][pos.getXPos()];
}
