#include "SmartStrategy.h"


//implementation using BFS	Algorithem.
Direction SmartStrategy::getNextDir(Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos)
{
	Direction resDir;
	int AddOrReduceRow[4] = { -1,0,1,0 }; //Up, Left, Down, Right
	int AddOrReduceCol[4] = { 0,-1,0,1 };

	// Visited vector to so that
	// a vertex is not visited more than once
	// Initializing the vector to false as no
	// vertex is visited at the beginning
	bool visited[25][80] = {};
	//vector<Position> q;
	queue<Position> q;
	//q.push_back(pacmanPos);
	q.push(pacmanPos);

	// Set source as visited
	visited[pacmanPos.getYPos()][pacmanPos.getXPos()] = true;

	Position temp;
	while (!q.empty())
	{
		temp = q.front();

		// Print the current node
		//cout << vis << " ";
		//q.erase(q.begin());
		q.pop();

		// For every adjacent vertex to the current vertex
		for (int i = 0; i < 4; i++)
		{
			int neighborX = temp.getXPos() + AddOrReduceCol[i];
			int neighborY = temp.getYPos() + AddOrReduceRow[i];

			if ( !(visited[neighborY][neighborX]) && isNeighborCellIsGhost(creatureCurrPos, neighborY, neighborX) )
			{
				convertNeighborsToDirection(resDir, AddOrReduceRow[i], AddOrReduceCol[i]);
				//setCurrPos(temp);
				return resDir;
			}
			else if ( !(isNeighborCellIsGhost(creatureCurrPos, neighborY, neighborX)) && !(visited[neighborY][neighborX]) )
			{
				if ( (board.getCellInBoard(neighborX, neighborY) != GameBoard::BORDER) && (board.getCellInBoard(neighborX, neighborY) != GameBoard::TUNNEL) )
				{
					temp.setXPos(neighborX);
					temp.setYPos(neighborY);
					// Push the adjacent node to the queue
					//q.push_back(temp);
					q.push(temp);
					// Set
					visited[neighborY][neighborX] = true;
				}
			}
		}
	}
}

bool SmartStrategy::isNeighborCellIsGhost(Position& creatureCurrPos, int neighborY, int neighborX)
{
	Position tmpNeighbor(neighborX, neighborY);

	if (tmpNeighbor == creatureCurrPos)
		return true;
	return false;
}

void SmartStrategy::convertNeighborsToDirection(Direction& resDir, int _addedY, int _addedX)
{
	//if (creatureCurrPos.getXPos() == _addedX)
	if (_addedX == 1)
	{
		resDir = Direction::LEFT;
		//return;
	}
	if (_addedX == -1)
	{
		resDir = Direction::RIGHT;
		//return;
	}
	if (_addedY == 1)
	{
		resDir = Direction::UP;
		//return;
	}
	if (_addedY == -1)
	{
		resDir = Direction::DOWN;
		//return;
	}
}