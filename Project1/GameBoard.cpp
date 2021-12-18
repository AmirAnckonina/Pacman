#include "GameBoard.h"
#include "Position.h"
#include "ThePacmanGame.h" 


//void GameBoard::readTemplateFromFile()
//{
	//ifstream templateFile(boardTemplates[currTemplate++], std::ios::in);
	//if (templateFile)
	//{
	//	readRawTemplate(templateFile);
	//	//templateFile.close();
	//}
	//else
	//{
	//	validBoard = false;
	//	return;
	//}
//}

/*
void GameBoard::readRawTemplate(ifstream& templateFile)
{
	int rowInd = 0, colInd = 0, countFirstLineCols = 0;
	char tmpChar;
	bool flag = false, inFirstRow = true;

	tmpChar = templateFile.get();

	if (isEmptyFile(tmpChar))
	{
		cout << "Empty File";
		validBoard = false;
	}

	if (validBoard)
	{

		while (tmpChar != EOF && validBoard) //&& rowInd < ROWMAX)
		{
			if (tmpChar == '\n' && inFirstRow)
				inFirstRow = false;

			if (inFirstRow)
				countFirstLineCols++;

			if (tmpChar != '\n')
				if (rowInd > ROWMAX || colInd > COLMAX)
					validBoard = false;

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


	if (rowInd <= 1 && countFirstLineCols == 0)
	{
		cout << "invalid board." << endl;
		validBoard = false;
	}

	lastRow = rowInd - 1;
	lastCol = countFirstLineCols - 1;
	firstCol = 0;
	firstRow = 0;
}
*/

void GameBoard::setBreadCrumbsPosArr()
{
	int k = 0;
	for (int i = 0; i <= lastRow; i++)
	{
		for (int j = 0; j <= lastCol; j++)
			if (board[i][j] == BREADCRUMB)
			{
				Position newPos(j, i);
				validPosStorage.push_back(newPos);
			}
	}
}


void GameBoard::readRawTemplate() //(ifstream& templateFile)
{
	ifstream templateFile(boardTemplates[currTemplate++], std::ios::in);

	if (!templateFile)
	{
		printInvalidBoardError(RETRIEVE);
		validBoard = false;
		return;
	}

	int rowInd = 0, colInd = 0;
	int colsInFirstRow = 0;
	char tmpChar;
	//bool flag = false, inFirstRow = true;

	tmpChar = templateFile.get();

	/*if(isEmptyTemplate(tmpChar))
	{
		printInvalidBoardError(EMPTYFILE);
		Sleep(2000);
		validBoard = false;
		return;
	}*/

	handleFirstRow(templateFile, tmpChar, colsInFirstRow);
	rowInd = 1;

	tmpChar = templateFile.get();
	while (tmpChar != EOF && validBoard)
	{
		if (tmpChar == '\n')
		{
			rowInd++;
			colInd = 0;
		}
		else // if != '\n'
		{
			if (colInd >= COLMAX)
			{
				printInvalidBoardError(TOOWIDE);
				validBoard = false;
			}
			else if (validBoard)
			{
				tmpChar = convertChar(tmpChar);
				board[rowInd][colInd++] = tmpChar;
			}
		}

		if (validBoard && rowInd > ROWMAX)
		{
			printInvalidBoardError(TOOLONG);
			validBoard = false;
		}

		tmpChar = templateFile.get();
	}


	if (validBoard)
		setBoardFrame(rowInd - 1, colsInFirstRow - 1);

	templateFile.close();
}

void GameBoard::handleFirstRow(ifstream& templateFile, char& tmpChar, int& colsCounter)
{
	int rowInd = 0;
	//firstChar got in previous function already.
	while (tmpChar != EOF && tmpChar != '\n' && validBoard)
	{
		if (colsCounter >= COLMAX)
		{
			printInvalidBoardError(TOOWIDE);
			validBoard = false;
		}
		else
		{
			tmpChar = convertChar(tmpChar);
			board[rowInd][colsCounter++] = tmpChar;
		}
		tmpChar = templateFile.get();
	}

	if (colsCounter == 0)
	{
		printInvalidBoardError(EMPTYFILE);
		validBoard = false;
	}
}


bool GameBoard::isEmptyTemplate(char ch)
{
	if (ch == '\n')
		return true;
	return false;
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

void GameBoard::setBoardFrame(int _lastRow, int _lastCol)
{
	lastRow = _lastRow;
	lastCol = _lastCol;
	firstCol = 0;
	firstRow = 0;
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
	{
		for (colInd = 0; colInd < COLMAX; colInd++)
		{
			board[rowInd][colInd] = SPACE;
		}
	}
	validBoard = true;
}

void GameBoard::initBoard()
{
	borderColor = breadcrumbColor = tunnelColor = Colors::WHITE;
	totalBreadcrumbs = 0;

	resetBoard();
	readRawTemplate();

	if (validBoard)
	{
		initInvisibleTunnels();
		//countTotalBreadcrumbs();
		//printBoard();
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

			if (board[rowInd][colInd] == LEGEND)
				cout << GameBoard::SPACE;
			else
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

size_t GameBoard::getValidPosStorage() const
{
	return validPosStorage.size();
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

void GameBoard::printInvalidBoardError(int errorCode) const
{
	cout << "Screen No. " << currTemplate << " ERROR." << endl;
	switch (errorCode)
	{
	case EMPTYFILE:
		cout << "Sorry! The system recognized an EMPTY screen." << endl;
		cout << "Please check your screen files.";
		break;
	case RETRIEVE:
		cout << "Sorry! screen file DIDN'T FOUND." << endl;
		cout << "Or we might have memory problem, try again later!";
		break;
	case TOOLONG:
		cout << "Sorry! The recieved screen is TOO LONG." << endl;
		cout << "We recommend you to shorten the length of board's rows.";
		break;
	case TOOWIDE:
		cout << "Sorry! The recieved screen is TOO WIDE." << endl;
		cout << "We recommend you to shorten the width of board's cols.";
		break;
	default:
		cout << "Invalid board.";
		break;
	}

	Sleep(5000);
	clearScreen();
}