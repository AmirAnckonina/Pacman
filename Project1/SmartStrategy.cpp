#include "SmartStrategy.h"

Position SmartStrategy::getNewPosByStrategy(const Position& creatureCurrPos, GameBoard& board, const Position& pacmanPos, Direction& creatureDirection, const char creatureIcon)
{
	Position newNextPos;
	setNextPosBFS(board, creatureCurrPos, pacmanPos, newNextPos);
	return newNextPos;
}

void SmartStrategy::setNextPosBFS(GameBoard& board, const Position& creatureCurrPos, const Position& pacmanPos, Position& newNextPos)
{
	//Position srcPos = pacmanPos;
	//Position dstPos = creatureCurrPos;
	Position adjCoord, currCoord;

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

	while (!q.empty())
	{
		currCoord = q.front();
		// Print the current node
		q.pop();
		// For every adjacent vertex to the current vertex
		for (int i = 0; i < 4; i++)
		{
			adjCoord.setXPos(currCoord.getXPos() + AddOrReduceCol[i]);
			adjCoord.setYPos(currCoord.getYPos() + AddOrReduceRow[i]);

			if (adjCoord == creatureCurrPos)
			{
				//creature.setNextPos(tmpPos);
				newNextPos = currCoord;
				return;
			}
			else if (!(visited[adjCoord.getYPos()][adjCoord.getXPos()]) && (cellShouldEnterQueue(board, adjCoord)))
			{
				// Push the adjacent node to the queue
				q.push(adjCoord);
				// Set
				visited[adjCoord.getYPos()][adjCoord.getXPos()] = true;
			}
		}
	}
}

bool SmartStrategy::cellShouldEnterQueue(GameBoard& board, Position& adjCoord)
{
	if (board.getCellInBoard(adjCoord) != GameBoard::BORDER)
	{
		if (board.getCellInBoard(adjCoord) != GameBoard::TUNNEL)
		{
			return true;
		}
	}
	return false;
}

bool SmartStrategy::isNeighborCellIsGhost(const Position& creatureCurrPos, int neighborY, int neighborX)
{
	Position tmpNeighbor;
	tmpNeighbor.setXPos(neighborX);
	tmpNeighbor.setYPos(neighborY);

	if (tmpNeighbor == creatureCurrPos)
	{
		return true;
	}
	return false;
}

//implementation using BFS Algorithem.

////implementation using BFS Algorithem.
//void SmartStrategy::setNextPosBFS(GameBoard& board, const Position& creatureCurrPos, const Position& pacmanPos, Position& newNextPos)
//{
//	//Position srcPos = pacmanPos;
//	//Position dstPos = creatureCurrPos;
//	Position tmpPos;
//
//	int AddOrReduceRow[4] = { -1,0,1,0 }; //Up, Left, Down, Right
//	int AddOrReduceCol[4] = { 0,-1,0,1 };
//
//	// Visited vector to so that
//	// a vertex is not visited more than once
//	// Initializing the vector to false as no
//	// vertex is visited at the beginning
//	bool visited[25][80] = {};
//	//vector<Position> q;
//	queue<Position> q;
//	//q.push_back(pacmanPos);
//	q.push(pacmanPos);
//
//	// Set source as visited
//	visited[pacmanPos.getYPos()][pacmanPos.getXPos()] = true;
//
//	while (!q.empty())
//	{
//		tmpPos = q.front();
//
//		// Print the current node
//		q.pop();
//
//		// For every adjacent vertex to the current vertex
//		for (int i = 0; i < 4; i++)
//		{
//			int neighborX = tmpPos.getXPos() + (AddOrReduceCol[i]);
//			int neighborY = tmpPos.getYPos() + (AddOrReduceRow[i]);
//
//			if (isNeighborCellIsGhost(creatureCurrPos, neighborY, neighborX) && !(visited[neighborY][neighborX]))
//			{
//				//creature.setNextPos(tmpPos);
//				newNextPos = tmpPos;
//				return;
//			}
//
//			else if (!(isNeighborCellIsGhost(creatureCurrPos, neighborY, neighborX)) && !(visited[neighborY][neighborX]))
//			{
//				if (cellShouldEnterQueue(board, neighborY, neighborX))
//				{
//					tmpPos.setXPos(neighborX);
//					tmpPos.setYPos(neighborY);
//					// Push the adjacent node to the queue
//					q.push(tmpPos);
//					// Set
//					visited[neighborY][neighborX] = true;
//				}
//			}
//		}
//	}
//}


/*
void SmartStrategy::executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos)
{
	setNextPosBFS(board, creature, pacmanPos);
}

//implementation using BFS	Algorithem.
void SmartStrategy::setNextPosBFS(GameBoard& board, Creature& creature, const Position& pacmanPos)
{
	Position srcPos = pacmanPos;
	Position dstPos = creature.getCurrPos();
	Position tmpPos;

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
	q.push(srcPos);

	// Set source as visited
	visited[srcPos.getYPos()][srcPos.getXPos()] = true;

	while (!q.empty())
	{
		tmpPos = q.front();

		// Print the current node
		//cout << vis << " ";
		//q.erase(q.begin());
		q.pop();

		// For every adjacent vertex to the current vertex
		for (int i = 0; i < 4; i++)
		{
			int neighborX = tmpPos.getXPos() + AddOrReduceCol[i];
			int neighborY = tmpPos.getYPos() + AddOrReduceRow[i];

			if ( !(visited[neighborY][neighborX]) && isNeighborCellIsGhost(dstPos, neighborY, neighborX) )
			{
				creature.setNextPos(tmpPos);
			}
			else if ( !(isNeighborCellIsGhost(dstPos, neighborY, neighborX)) && !(visited[neighborY][neighborX]) )
			{
				if ( (board.getCellInBoard(neighborX, neighborY) != GameBoard::BORDER) && (board.getCellInBoard(neighborX, neighborY) != GameBoard::TUNNEL) )
				{
					tmpPos.setXPos(neighborX);
					tmpPos.setYPos(neighborY);
					// Push the adjacent node to the queue
					//q.push_back(temp);
					q.push(tmpPos);
					// Set
					visited[neighborY][neighborX] = true;
				}
			}
		}
	}
}
*/


