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

void Position::setNextPos(Direction dir, char figure)
{
	//Pay attention while pacman goes through a tunnel cell, he wiil be placed in the other side
	//This function does NOT check if next position is Valid, just set a new potenital position, for every creature that need.
	switch (dir)
	{
	case Direction::UP:
		_y -= 1;
		break;

	case Direction::DOWN:
		_y += 1;
		break;

	case Direction::LEFT:
		if (_x == 1 && _y > 10 && _y < 14)
		{
			if (figure == Pacman::PACMAN) _x = 78;
			else _x = 0;
		}
		else
			_x -= 1;
		break;

	case Direction::RIGHT:
		if (_x == 78 && _y > 10 && _y < 14)
		{
			if (figure == Pacman::PACMAN) _x = 1;
			else _x = 79;
		}
		else 
			_x += 1;
		break;

	default: //STAY
		break;
	}
}


