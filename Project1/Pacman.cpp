#include "Pacman.h"
#include "ThePacmanGame.h"

void Pacman::initPacman()
{
	score = 1; //Pacman will be placed on (1,1) coordinate which has a breadcrumb, so the score will start from 1.
	livesLeft = 3;
	pacmanColor = Colors::WHITE;
	setPacmanPosition();
}

void Pacman::setPacmanPosition()
{
	currPos.setXPos();
	currPos.setYPos();
	pacmanDirection = Direction::STAY;
	nextPos = currPos;
	pacmanDirection = Direction::STAY;
}

void Pacman::movePacman(GameBoard& board)
{
	//Set potential new position to pacman, then check if it's valid.
	nextPos.setNextPos(pacmanDirection, PACMAN);
	if (pacmanDirection != Direction::STAY && nextPos.isPositionValid(board, PACMAN)) //So we should move the pacman
	{
		if (board.getCellInBoard(currPos) != GameBoard::TUNNEL)
			board.setCellInBoard(currPos, GameBoard::SPACE);

		//print space in current position because soon pacman will be moved.
		gotoxy(currPos.getXPos(), currPos.getYPos());
		cout << GameBoard::SPACE;
	}
	else //In case not, please stay on the current position.
	{
		nextPos = currPos;
		pacmanDirection = Direction::STAY;
	}
}

void Pacman::printPacman() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ThePacmanGame::isGameColorized()) { setTextColor(pacmanColor); }
	cout << PACMAN;
}

void Pacman::updateScore(GameBoard& board)
{
	if (pacmanDirection != Direction::STAY && board.getCellInBoard(nextPos) == GameBoard::BREADCRUMB)
		score++;
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