#include "Ghost.h"
#include "ThePacmanGame.h"
#include "Menu.h"
//

Ghost::Ghost(char _ghostIcon, int _ghostLevel) : Creature(_ghostIcon), ghostLevel(_ghostLevel) {}

void Ghost::initGhost(GameBoard& board, int level)
{
	ghostLevel = level;
	convertGhostLevelToStrategy();
	setCreatureStrategyType(ghostLevel);
	initCreature(board, '$');
}

void Ghost::convertGhostLevelToStrategy()
{
	switch (ghostLevel)
	{
	case GOOD:
	case BEST:
	case EXTREME:
		setCreatureStrategyType(SMART);
		break;
	case NOVICE:
		setCreatureStrategyType(NORMAL);
		break;
	default:
		break;
	}
}
/*
void Ghost::moveGhost(GameBoard& board, const Position& pacmanPos)
{
	setCreatureNextPos(board);
	while ( !(isCreaturePositionValid(board)) )
	{
		//RollBack
		resetAfterInvalidNextPos();
		//generateRandomDirection();
		setCreatureNextPos(board);
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
*/
/*
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

*/
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

