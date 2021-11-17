
#include "ghost.h"

void Ghost::moveGhost(GameBoard& board)
{
	bool isValid = false;

	while (!isValid)
	{
		setRandomDirection();
		nextPos.setNextPos(ghDirecrtion);
		isValid = nextPos.isPositionValid(board, ghostFigure);
		if (!isValid)
			nextPos = currPos;
	}

	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (board.getCellInBoard(currPos) == BREADCRUMB)//the ghost moved and we want the board to return to the way it was.
	{
		if (board.getBreadcrumbColor() != gameColors::WHITE) setTextColor(board.getBreadcrumbColor());
		cout << BREADCRUMB;
	}
	else cout << SPACE;
}

void Ghost::initGhost(int xCoord, int yCoord)
{
	ghostColor = gameColors::WHITE;
	setGhostLocation(xCoord, yCoord);
}

void Ghost::setGhostLocation(int xCoord, int yCoord)
{
	currPos.setXPos(xCoord);
	currPos.setYPos(yCoord);
	nextPos = currPos; //Prevent a bug in the beginning which the ghost jumped to the pacman location
}

void Ghost::printGhost()
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ghostColor != gameColors::WHITE) { setTextColor(ghostColor); }
	cout << ghostFigure;
}

void Ghost::setRandomDirection()
{
	int dirInd = rand() % 4 + 1;

	switch (dirInd)
	{
	case 1://up
		ghDirecrtion = Direction::UP;
		break;

	case 2://down
		ghDirecrtion = Direction::DOWN;
		break;

	case 3://left
		ghDirecrtion = Direction::LEFT;
		break;

	case 4://right
		ghDirecrtion = Direction::RIGHT;
		break;

	default:
		break;
	}

}