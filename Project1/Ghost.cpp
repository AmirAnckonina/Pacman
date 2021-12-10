#include "Ghost.h"
#include "ThePacmanGame.h"
//

Ghost::Ghost(char _ghostIcon) : Creature(_ghostIcon) {}
//Ghost::Ghost(Position _ghostStartingPos, Position _ghostCurrPos, Position _ghostNextPos, Direction _ghostDirection, Colors _ghostColor, char _ghostIcon)
//	: Creature(_ghostStartingPos ,_ghostCurrPos, _ghostNextPos, _ghostDirection, _ghostColor, _ghostIcon) {}

void Ghost::initGhost(GameBoard& board)
{
	//Startegy
	initCreature(board, '$');
}


void Ghost::moveGhost(GameBoard& board)
{
	bool isValid = false;
	while (!isValid)
	{
		//Set potential new position to ghost, then check if it's valid.
		generateRandomDirection();
		setCreatureNextPos(board);
		isValid = isCreaturePositionValid(board);
		if (!isValid) //Rollback, before starting the loop again
		{
			resetNextPos();
			setDirection(Direction::STAY);
		}
	}

	gotoxy(getCurrPos().getXPos(), getCurrPos().getYPos());
	//The ghost printed and we want the print of the cell as it were before.
	if (board.getCellInBoard(getCurrPos()) == GameBoard::BREADCRUMB)
	{
		if (ThePacmanGame::isGameColorized())
			setTextColor(board.getBreadcrumbColor());
		cout << GameBoard::BREADCRUMB;
	}
	else
		cout << GameBoard::SPACE;
}

void Ghost::generateRandomDirection()
{
	int dirInd = rand() % 4 + 1;
	switch (dirInd)
	{
	case 1:
		setDirection(Direction::UP);
		break;
	case 2:
		setDirection(Direction::DOWN);
		break;
	case 3:
		setDirection(Direction::LEFT);
		break;
	case 4:
		setDirection(Direction::RIGHT);
		break;
	default:
		break;
	}

}
/*
//implementation using BFS	Algorithem.
void Ghost::smartGhostMove(GameBoard& board, const Position& pacmanPos)
{
	int AddOrReduceRow[4] = { -1,0,1,0 }; //Up, Left, Down, Right
	int AddOrReduceCol[4] = { 0,-1,0,1 };
	
	// Visited vector to so that
	// a vertex is not visited more than once
	// Initializing the vector to false as no
	// vertex is visited at the beginning
	bool visited[80][25] = {};
	vector<Position> q;
	q.push_back(pacmanPos);

	// Set source as visited
	visited[pacmanPos.getXPos()][pacmanPos.getYPos()] = true;

	Position temp;
	while (!q.empty())
	{
		temp = q[0];

		// Print the current node
		//cout << vis << " ";
		q.erase(q.begin());

		// For every adjacent vertex to the current vertex
		for (int i = 0; i < 4; i++) 
		{
			int neighborX = temp.getXPos() + AddOrReduceRow[i];
			int neighborY = temp.getYPos() + AddOrReduceCol[i];

			if (!(visited[temp.getXPos()][neighborY]) && neighborX == getCurrPos().getXPos() && neighborY == getCurrPos().getYPos())
			{
				setCurrPos(temp);
				return;

			}
			else if ((neighborX != getCurrPos().getXPos() || neighborY != getCurrPos().getYPos()) && !(visited[temp.getXPos()][neighborY]))
			{
				if (board.getCellInBoard(neighborX, neighborY) != GameBoard::BORDER && board.getCellInBoard(neighborX, neighborY) != GameBoard::TUNNEL)
				{
					temp.setXPos(neighborX);
					temp.setYPos(neighborY);
					// Push the adjacent node to the queue
					q.push_back(temp);
					// Set
					visited[neighborX][neighborY] = true;
				}
			}
		}
	}
}
*/


