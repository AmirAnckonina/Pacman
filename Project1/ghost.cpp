#include "ghost.h"

void Ghost::initGhost(int xCoord, int yCoord)
{
	ghostColor = Colors::WHITE;
	setGhostPosition(xCoord, yCoord);
}

void Ghost::setGhostPosition(int xCoord, int yCoord)
{
	currPos.setXPos(xCoord);
	currPos.setYPos(yCoord);
	nextPos = currPos;
}

void Ghost::moveGhost(GameBoard& board)
{
	bool isValid = false;
	while (!isValid)
	{
		//Set potential new position to ghost, then check if it's valid.
		setRandomDirection();
		nextPos.setNextPos(ghostDirection, GHOST);
		isValid = nextPos.isPositionValid(board, GHOST);
		if (!isValid) //rollback, before starting the loop again.
			nextPos = currPos;
	}

	//The ghost printed and we want the print the cell as it were before.
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (board.getCellInBoard(currPos) == GameBoard::BREADCRUMB)
	{
		if (board.getBreadcrumbColor() != Colors::WHITE) { setTextColor(board.getBreadcrumbColor()); }
		cout << GameBoard::BREADCRUMB;
	}
	else cout << GameBoard::SPACE;
}

void Ghost::printGhost() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ghostColor != Colors::WHITE) { setTextColor(ghostColor); }
	cout << GHOST;
}

void Ghost::setRandomDirection()
{
	int dirInd = rand() % 4 + 1;

	switch (dirInd)
	{
	case 1:
		ghostDirection = Direction::UP;
		break;

	case 2:
		ghostDirection = Direction::DOWN;
		break;

	case 3:
		ghostDirection = Direction::LEFT;
		break;

	case 4:
		ghostDirection = Direction::RIGHT;
		break;
	default:
		break;
	}
}