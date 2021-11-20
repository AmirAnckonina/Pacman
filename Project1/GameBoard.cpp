#include "GameBoard.h"
#include "ThePacmanGame.h" 

void GameBoard::initBoard()
{
	borderColor = breadcrumbColor = tunnelColor = Colors::WHITE;
	boardColorized = false;
	totalBreadcrumbs = 0;
	initOuterBorders();
	initInnerWalls();
	initBreadcrumbs();
	initDetailsArea();
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
			if (ThePacmanGame::isGameColorized()) boardColorizedProcedure(rowInd, colInd);
			cout << _board[rowInd][colInd];
		}
		if (colInd < COLMAX - 1) 
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
