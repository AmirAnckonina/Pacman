#include "Pacman.h"
#include "ThePacmanGame.h"

Pacman::Pacman(char _pacmanIcon) : Creature(_pacmanIcon) {}

void Pacman::move(GameBoard& board, const Position& pacmanPos)
{
	//Set potential new position to pacman, then check if it's valid.
	setCreatureNextPos(board);
	if (!isCreaturePositionValid(board))
	{
		//nextPosIsValid = false;
		setNextPosIsValid(false);
		resetAfterInvalidNextPos();
	}
	else //nextPosIsValid = true;
		setNextPosIsValid(true);

}

void Pacman::afterMoveProcedure(GameBoard& board)
{
	if (getNextPosIsValid()) //So we should move the pacman //getDirection() != Direction::STAY && 
	{
		//print space in current position because soon the pacman will be moved.
		gotoxy(getPrevPos().getXPos(), getPrevPos().getYPos());
		if (board.getCellInBoard(getPrevPos()) != GameBoard::TUNNEL)
		{
			cout << GameBoard::SPACE;
		}
		else
		{
			if (ThePacmanGame::isGameColorized())
				setTextColor(board.getTunnelColor());

			cout << GameBoard::TUNNEL;
		}
	}
}

//void Pacman::
void Pacman::updateScore(GameBoard& board)
{
	//Collect score if breadCrumb placed in currPos
	if (board.getCellInBoard(getNextPos()) == GameBoard::BREADCRUMB)
		score++;
}

Direction Pacman::convertKeyToDirection(char key) const
{
	//Key translation to Direction
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
