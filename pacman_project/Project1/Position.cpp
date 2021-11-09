#include <iostream>
#include "Position.h"

//Recieved board by reference and return true or false whether the reqired position to move to is valid.
bool Position::isPositionValid(GameBoard& board) 
{
	if (board.getCellInBoard(_x, _y) == BORDER)
		return false;
	return true;
}


//Gotoxy implemtation.
void Position::gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
