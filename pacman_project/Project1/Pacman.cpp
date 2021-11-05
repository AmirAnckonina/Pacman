//pacman.cpp

#include "Pacman.h"


void Pacman::movePacman(int currX, int currY)
{
	cin >> currUserDirection;
	while (!isMoveValid)
	{
		cin >> currUserDirection;
	}
	board[currX][currY] = board.space;//puts white space in the previous location of the pacman
	currPoint.gotoxy(currX, currY);
	cout << board.space;
	switch (currUserDirection)
	{
	case UP:
		currY -= 1;

	case DOWN:
		board[currX][currY] = board.space;
		if (board[currX][currY + 1] == board.breadCrumb)
			score++;
		currPoint.gotoxy(currX, currY);
		cout << board.space;
		Sleep(100);
		currY -= 1;
		currPoint.gotoxy(currX, currY);
		cout << PacmanArtifact;
	case LEFT:
	case RIGHT:

	default:
		break;
	}

}
bool Pacman::isMoveValid()
{
	if (board[currXInd][currYind] != space || board[currXInd][currYind] != breadCrumb)
		return false;
	return true;
}
void Pacman::updateBoard(char Direction)
{

}