#include "Pacman.h"

int Pacman::score = 0;
int Pacman::livesLeft = 3;

//Set pacman on board.
void Pacman::setPacman() //Note if should gave by ref
{
	pacDirection = STAY;
	currPos.gotoxy(currPos.getXPos(), currPos.getYPos());//print the pacman on board
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

		/*if (board.getCellInBoard(nextPos) == BREADCRUMB)
		{
			score++;
			currPos.gotoxy(20, 26);
			cout << "                                ";
			cout << "The score is = " << score;
		}*/

		currPos.gotoxy(currPos.getXPos(), currPos.getYPos());
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
		currPos.gotoxy(0, 26);
		cout << "                                ";
		cout << "The score is = " << score;
	}
}

void Pacman::printPacman()
{
	currPos.gotoxy(currPos.getXPos(), currPos.getYPos());//print the pacman on board
	cout << pacmanFigure;
}


//Feels like a very stupid function, maybe we can arrange it better?
char Pacman::getDirection(char key) const
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