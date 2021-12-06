#include "Position.h"
#include "Pacman.h"
#include "Ghost.h"

bool Position::isPositionValid(GameBoard& board, char figure)
{

	char cellCh = board.getCellInBoard(_x, _y);

	if (cellCh == GameBoard::BORDER)
		return false;
	if (cellCh == GameBoard::TUNNEL && figure == Ghost::GHOST) //Prevent ghost to move through the tunnels.
		return false;
	//Otherwise
	return true;
}

void Position::setNextPos(Direction dir, char figure, GameBoard& board)
{
	//Pay attention while pacman goes through a tunnel cell, he wiil be placed in the other side
	//This function does NOT check if next position is Valid, just set a new potenital position, for every creature that need.
	switch (dir)
	{
	case Direction::UP:
		if (board.getCellInBoard(_x, _y - 1) == GameBoard::TUNNEL)
		{
			if (figure == Pacman::PACMAN) _y = board.getLastRow() - 1;
			else _y = board.getFirstRow();
		}
		else
			_y -= 1;
		break;

	case Direction::DOWN:
		if (board.getCellInBoard(_x, _y + 1) == GameBoard::TUNNEL)
		{
			if (figure == Pacman::PACMAN) _y = board.getFirstRow() + 1;
			else _y = board.getLastRow();
		}
		else
			_y -= 1;
		break;

	case Direction::LEFT:
		//if (_x-1 == board.isFirstCol() && _y > 10 && _y < 14)
		if (board.getCellInBoard(_x - 1, _y) == GameBoard::TUNNEL)
		{
			if (figure == Pacman::PACMAN) _x = board.getLastCol() - 1;
			else _x = board.getFirstCol();
		}
		else
			_x -= 1;
		break;

	case Direction::RIGHT:
		//if (_x == 78 && _y > 10 && _y < 14)
		if (board.getCellInBoard(_x + 1, _y) == GameBoard::TUNNEL)
		{
			if (figure == Pacman::PACMAN) _x = board.getFirstCol() + 1;
			else _x = board.getLastCol();
		}
		else
			_x += 1;
		break;

	default: //STAY
		break;
	}
}


