#include "Position.h"
#include "Creature.h"
//#include "Pacman.h"
//#include "Ghost.h"
//test


bool Position::isPositionValid(GameBoard& board, char figure))

{

	if( !(board.inBoardDimensions(x, y)) )
		return false;
	char cellCh = board.getCellInBoard(x, y);
	if (cellCh == GameBoard::BORDER)
		return false;
	if (cellCh == GameBoard::TUNNEL && figure == Creature::GHOST) //Prevent ghost to move through the tunnels.
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
		if (board.getCellInBoard(x, y - 1) == GameBoard::TUNNEL)
		{
			if (figure == Creature::PACMAN && board.getCellInBoard(x, board.getLastRow()) != GameBoard::BORDER) y = board.getLastRow() - 1;
			else y = board.getFirstRow();
		}
		else
			y -= 1;
		break;

	case Direction::DOWN:
		if (board.getCellInBoard(x, y + 1) == GameBoard::TUNNEL)
		{
			if (figure == Creature::PACMAN && board.getCellInBoard(x, board.getFirstRow()) != GameBoard::BORDER) y = board.getFirstRow() + 1;
			else y = board.getLastRow();
		}
		else
			y += 1;
		break;

	case Direction::LEFT:
		//if (_x-1 == board.isFirstCol() && _y > 10 && _y < 14)
		if (board.getCellInBoard(x - 1, y) == GameBoard::TUNNEL)
		{
			if (figure == Creature::PACMAN && board.getCellInBoard(board.getLastCol(), y) != GameBoard::BORDER)
				x = board.getLastCol() - 1;
			else
				x = board.getFirstCol();
		}
		else
			x -= 1;
		break;

	case Direction::RIGHT:
		//if (_x == 78 && _y > 10 && _y < 14)
		if (board.getCellInBoard(x + 1, y) == GameBoard::TUNNEL)
		{
			if (figure == Creature::PACMAN && board.getCellInBoard(board.getFirstCol(), y) != GameBoard::BORDER) x = board.getFirstCol() + 1;
			else x = board.getLastCol();
		}
		else
			x += 1;
		break;

	default: //STAY
		break;
	}
}


