#include "Pacman.h"

//Set pacman on board.
void Pacman::initPacman() //Note if should gave by ref
{
	score = 0;
	livesLeft = 3;
	pacColor = gameColors::WHITE;
	setPacmanLocation();
}

void Pacman::setPacmanLocation()
{
	currPos.setXPos();
	currPos.setYPos();
	nextPos = currPos;
}

//Move pacman - important. also updating currPos according to inner condition.
void Pacman::movePacman(GameBoard& board)
{
	//Setting new potential position to pacman
	nextPos.setNextPos(pacmanDirection, pacmanFigure);
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

void Pacman::printPacman()
{
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