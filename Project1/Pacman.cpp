#include "Pacman.h"

//Set pacman on board.
void Pacman::setPacman() //Note if should gave by ref
{
	pacmanDirection = userKeys::STAY;
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
	nextPos.setNextPos(pacmanDirection);
	//Stage 1 - validation check (to the cell)
	if (pacmanDirection != Direction::STAY && nextPos.isPositionValid(board, pacmanFigure)) //So we should move the pacman
	{
		if (board.getCellInBoard(currPos) != TUNNEL)
			board.setCellInBoard(currPos, SPACE);

		gotoxy(currPos.getXPos(), currPos.getYPos());
		cout << SPACE;
	}
	else
	{
		nextPos = currPos;
		pacmanDirection = STAY;
	}
}

void Pacman::updateScore(GameBoard& board)
{
	if (pacmanDirection != Direction::STAY && board.getCellInBoard(nextPos) == BREADCRUMB)
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
	////We should have a condition that checks if the pacDirecton != STAY
	//if (pacmanDirection != STAY)
	//{
	//	gotoxy(currPos.getXPos(), currPos.getYPos());
	//	cout << SPACE;
	//}

	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (pacColor != gameColors::WHITE) { setTextColor(pacColor); }
	cout << pacmanFigure;
}


//Feels like a very stupid function, maybe we can arrange it better?
Direction Pacman::getDirection(char key) const
{
	switch (key)
	{
	case 'w':
	case 'W':
		return Direction::UP;
	case 'x':
	case 'X':
		return Direction::DOWN;
	case 's':
	case 'S':
		return Direction::STAY;
	case 'd':
	case 'D':
		return Direction::RIGHT;
	case 'a':
	case 'A':
		return Direction::LEFT;
	default:
		return Direction::WRONG_KEY;
	}
}

void Pacman::setDirection(Direction dir)
{
	pacmanDirection = dir;
}