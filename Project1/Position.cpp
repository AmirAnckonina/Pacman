#include <iostream>
#include "Position.h"

//Recieved board by reference and return true or false whether the reqired position to move to is valid.
bool Position::isPositionValid(GameBoard& board, char figure)
{
	char cellCh = board.getCellInBoard(_x, _y);

	if (cellCh == BORDER)
		return false;
	if (cellCh == TUNNEL && figure == '$')
		return false;
	//Otherwise
	return true;
}

void Position::setNextPos(Direction dir)
{
	switch (dir)
	{
	case Direction::UP :
		_y -= 1;
		break;

	case Direction::DOWN :
		_y += 1;
		break;

	case Direction::LEFT :
		if (_x == 1 && _y > 10 && _y < 14)
			_x = 78;
		else
			_x -= 1;
		break;

	case Direction::RIGHT :
		if (_x == 78 && _y > 10 && _y < 14)
			_x = 1;
		else
			_x += 1;
		break;

	default: //STAY
		break;
	}
}



//Check Forum.
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}