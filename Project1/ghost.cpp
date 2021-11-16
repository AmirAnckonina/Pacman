
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

	//currPos.gotoxy(currPos.getXPos(), currPos.getYPos());
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (board.getCellInBoard(currPos) == BREADCRUMB)//the ghost moved and we want the board to return to the way it was.
	{
		setTextColor(board.getBreadcrumbColor());
		cout << BREADCRUMB;
	}
	else cout << SPACE;
}

void Ghost::setGhost(int xCoord, int yCoord)
{
	currPos.setXPos(xCoord);
	currPos.setYPos(yCoord);
	nextPos = currPos; //Prevent a bug in the beginning which the ghost jumped to the pacman location
	//currPos.gotoxy(xCoord, yCoord);//print the pacman on board
	gotoxy(xCoord, yCoord);
	cout << ghostFigure;
}



void Ghost::printGhost()
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	
	if (ghostColor != WHITE) { setTextColor(ghostColor); }
	cout << ghostFigure;
}

void Ghost::setRandomDirection()
{
	int dirInd = rand() % 4 + 1;

	switch (dirInd)
	{
	case 1://up
		ghDirecrtion = gameKeys::UP;
		break;

	case 2://down
		ghDirecrtion = ganeKeys::DOWN;
		break;

	case 3://left
		ghDirecrtion = LEFT;
		break;

	case 4://right
		ghDirecrtion = RIGHT;
		break;

	default:
		break;
	}

}