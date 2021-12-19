#include "Position.h"
#include "Creature.h"
#include "GameBoard.h"


bool Position::isPositionValid(GameBoard& board, char figure)
{
	if (!(board.inBoardDimensions(x, y)))
		return false;

	char cellCh = board.getCellInBoard(x, y);

	if (cellCh == GameBoard::BORDER)
		return false;

	if (figure == Creature::GHOST || figure == Creature::FRUIT)
	{
		if (cellCh == GameBoard::TUNNEL) //Prevent ghost to move through the tunnels.
			return false;
	}

	return true;

}
void Position::setNextPos(Direction dir, char figure, GameBoard& board)
{
	//Pay attention while pacman goes through a tunnel cell, he wiil be placed in the other side
	//This function does NOT check if next position is Valid, just set a new potenital position, for every creature that need.
	switch (dir)
	{
	case Direction::UP: //handleDirectionIsUP
		if (nextStepIsTunnel(board, x, y - 1) && y - 1 == board.getFirstRow())
		{
			if (tunnelAllowed(figure, board, x, board.getLastRow()))
				y = board.getLastRow() - 1;
			else y = board.getFirstRow();
		}
		else
			y -= 1;
		break;

	case Direction::DOWN:
		if (nextStepIsTunnel(board, x, y + 1) && y + 1 == board.getLastRow())
		{
			if (tunnelAllowed(figure, board, x, board.getFirstRow()))
				y = board.getFirstRow() + 1;
			else y = board.getLastRow();
		}
		else
			y += 1;
		break;

	case Direction::LEFT:
		if (nextStepIsTunnel(board, x - 1, y) && x - 1 == board.getFirstCol())
		{
			if (tunnelAllowed(figure, board, board.getLastCol(), y))
				x = board.getLastCol() - 1;
			else
				x = board.getFirstCol();
		}
		else
			x -= 1;
		break;

	case Direction::RIGHT:
		//if (_x == 78 && _y > 10 && _y < 14)
		if (nextStepIsTunnel(board, x + 1, y) && x + 1 == board.getLastCol())
		{
			if (tunnelAllowed(figure, board, board.getFirstCol(), y))
				x = board.getFirstCol() + 1;
			else
				x = board.getLastCol();
		}
		else
			x += 1;
		break;

	default: //STAY
		break;
	}
}

bool Position::nextStepIsTunnel(GameBoard& board, int x, int y)const
{
	if (x == board.getFirstCol() || x == board.getLastCol() || y == board.getFirstRow() || y == board.getLastRow())
	{
		if ((board.getCellInBoard(x, y) == GameBoard::TUNNEL) || (board.getCellInBoard(x, y) == GameBoard::SPACE))
		{
			return true;
		}
	}
	return false;
}

bool Position::tunnelAllowed(char figure, GameBoard& board, int x, int y)const
{
	if (figure == Creature::PACMAN && board.getCellInBoard(x, y) != GameBoard::BORDER)
		return true;
	return false;
}

bool Position::operator==(const Position& pos) const
{
	if (this->x == pos.getXPos() && this->y == pos.getYPos())
		return true;
	return false;
}
