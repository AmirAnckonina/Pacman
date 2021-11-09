#include "Pacman.h"

//Set pacman on board.
void Pacman::setPacman(GameBoard& board)
{
	board.setCellInBoard(currPos, pacmanFigure);
	currPos.gotoxy(currPos.getXPos(), currPos.getYPos());//print the pacman on board
	cout << pacmanFigure;
}

//Move pacman - important. also updating currPos according to inner condition.
void Pacman::movePacman(GameBoard& board)
{
	//Stage 1 - validation check (to the cell)
	if (pacDirection != STAY && nextPos.isPositionValid(board)) //So we should move the pacman
	{
		directionSaver = pacDirection;
		board.setCellInBoard(currPos, SPACE);
		if (board.getCellInBoard(nextPos) == BREADCRUMB)
		{
			score++;
		}
		board.setCellInBoard(nextPos, pacmanFigure);
		currPos.gotoxy(currPos.getXPos(), currPos.getYPos());
		cout << SPACE;
		//board.printCellInBoard(currPos);
		currPos = nextPos; //??????? Check later how to do it right
		currPos.gotoxy(currPos.getXPos(), currPos.getYPos());//print the pacman on board
		cout << pacmanFigure;
	}
	else
	{
		nextPos = currPos;
		pacDirection = STAY;
	}
} 
	
//Set next position, in order to check later if the next cell required is valid to move to.
void Pacman::setNextPos()
{
	int tmpX = currPos.getXPos();
	int tmpY = currPos.getYPos();

	switch (pacDirection)
	{
	case UP:
		tmpY -= 1;
		nextPos.setYPos(tmpY);
		break;

	case DOWN:
		tmpY += 1;
		nextPos.setYPos(tmpY);
		break;

	case LEFT:
		if (tmpX == 0 && tmpY > 10 && tmpY < 14)
			tmpX = 79;
		else
			tmpX -= 1;
		nextPos.setXPos(tmpX);
		break;

	case RIGHT:
		if (tmpX == 0 && tmpY > 10 && tmpY < 14)
			tmpX = 0;
		else
			tmpX += 1;
		nextPos.setXPos(tmpX);
		break;

	default: //STAY
		break;
	}
}

//Feels like a very stupid function, maybe we can arrange it better?
char Pacman::getDirection(char key)
{
	switch (key)
	{
	case UP:
	case DOWN:
	case STAY:
	case RIGHT:
	case LEFT:
		return key;
	default:
		return WRONG_KEY;
	}
}

void Pacman::setDirection(int direction)
{
	pacDirection = direction;
}

//void Pacman::setDirectionSaver(int direction)
//{
//	directionSaver = direction;
//}