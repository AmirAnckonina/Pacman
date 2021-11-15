#include "Pacman.h"




//Set pacman on board.
void Pacman::setPacman() //Note if should gave by ref
{
	pacDirection = STAY;
	//currPos.gotoxy(currPos.getXPos(), currPos.getYPos());//print the pacman on board
	gotoxy(currPos.getXPos(), currPos.getYPos());
	nextPos = currPos;
	cout << pacmanFigure;
}

void Pacman::resetPacman()
{
	currPos.setXPos();
	currPos.setYPos();
	setPacman();
}

//Move pacman - important. also updating currPos according to inner condition.
void Pacman::movePacman(GameBoard& board)
{
	//Setting new potential position to pacman
	nextPos.setNextPos(pacDirection);
	//Stage 1 - validation check (to the cell)
	if (pacDirection != STAY && nextPos.isPositionValid(board, pacmanFigure)) //So we should move the pacman
	{
		if (board.getCellInBoard(currPos) != TUNNEL)
			board.setCellInBoard(currPos, SPACE);

		//currPos.gotoxy(currPos.getXPos(), currPos.getYPos());
		gotoxy(currPos.getXPos(), currPos.getYPos());
		cout << SPACE;
	}
	else
	{
		nextPos = currPos;
		pacDirection = STAY;
	}
}

void Pacman::updateScore(GameBoard& board)
{
	if (pacDirection != STAY && board.getCellInBoard(nextPos) == BREADCRUMB)
	{
		score++;
		//currPos.gotoxy(0, 26);
		gotoxy(0, 26);
		cout << "                                ";
		cout << "The score is = " << score;
	}
}

void Pacman::printPacman()
{
	//currPos.gotoxy(currPos.getXPos(), currPos.getYPos());//print the pacman on board
	gotoxy(currPos.getXPos(), currPos.getYPos());
	cout << pacmanFigure;
}


//Feels like a very stupid function, maybe we can arrange it better?
char Pacman::getDirection(char key) const
{
	switch (key)
	{
	case 'w':
	case 'W':
		return UP;
	case 'x':
	case 'X':
		return DOWN;
	case 's':
	case 'S':
		return STAY;
	case 'd':
	case 'D':
		return RIGHT;
	case 'a':
	case 'A':
		return LEFT;
	default:
		return WRONG_KEY;
	}
}

void Pacman::setDirection(int direction)
{
	pacDirection = direction;
}