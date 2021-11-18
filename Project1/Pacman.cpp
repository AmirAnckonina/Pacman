#include "Pacman.h"

void Pacman::initPacman()
{
	score = 0;
	livesLeft = 3;
	pacColor = gameColors::WHITE;
	setPacmanPosition();
}

void Pacman::setPacmanPosition()
{
	currPos.setXPos();
	currPos.setYPos();
	pacmanDirection = Direction::STAY;
	nextPos = currPos;
}

void Pacman::movePacman(GameBoard& board)
{
	//Set potential new position to pacman, then check if it's valid.
	nextPos.setNextPos(pacmanDirection, pacmanFigure);
	if (pacmanDirection != Direction::STAY && nextPos.isPositionValid(board, pacmanFigure)) //So we should move the pacman
	{
		if (board.getCellInBoard(currPos) != TUNNEL)
			board.setCellInBoard(currPos, SPACE);

		//print space in current position because soon pacman will be moved.
		gotoxy(currPos.getXPos(), currPos.getYPos());
		cout << SPACE;
	}
	else //In case not, please stay on the current position.
	{
		nextPos = currPos;
		pacmanDirection = Direction::STAY;
	}
}

void Pacman::updateScore(GameBoard& board)
{
	if (pacmanDirection != Direction::STAY && board.getCellInBoard(nextPos) == BREADCRUMB)
	{
		score++;
		gotoxy(32, 13);
		cout << "                            ";
		gotoxy(32, 13);
		cout << "The score is = " << score;
	}
}

void Pacman::printPacman() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (pacColor != gameColors::WHITE) { setTextColor(pacColor); }
	cout << pacmanFigure;
}

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