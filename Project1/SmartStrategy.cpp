#include "SmartStrategy.h"
#include "Creature.h"


void SmartStrategy::executeMove(Creature& creature, GameBoard& board, const Position& pacmanPos)
{
	setNextPosBFS(board, creature, pacmanPos);
	return;
}

//implementation using BFS	Algorithem.
void SmartStrategy::setNextPosBFS(GameBoard& board, Creature& creature, const Position& pacmanPos)
{
	Position adjCoord, currCoord;

	int AddOrReduceRow[4] = { -1,0,1,0 }; //Up, Left, Down, Right
	int AddOrReduceCol[4] = { 0,-1,0,1 };

	// Visited vector to so that
	// a vertex is not visited more than once
	// Initializing the vector to false as no
	// vertex is visited at the beginning
	bool visited[25][80] = {};
	queue<Position> q;
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

			if (adjCoord == creature.getCurrPos())
			{
				creature.setDirection(convertAdjCoordToDirection(creature, adjCoord));
				creature.setNextPos(currCoord);
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
	if (!board.inBoardDimensions(adjCoord))
		return false;

	if (board.getCellInBoard(adjCoord) == GameBoard::BORDER)
		return false;

	if (board.getCellInBoard(adjCoord) == GameBoard::TUNNEL)
		return false;

	return true;
}

Direction SmartStrategy::convertAdjCoordToDirection(Creature& creature, Position& adjCoord)
{
	int creatureX = creature.getCurrPos().getXPos();
	int creatureY = creature.getCurrPos().getYPos();
	int adjCoordX = adjCoord.getXPos();
	int adjCoordY = adjCoord.getYPos();
	
	if (creatureY == adjCoordY + 1 && creatureX == adjCoordX)
		return Direction::UP;
	else if (creatureY == adjCoordY - 1 && creatureX == adjCoordX)
		return Direction::DOWN;
	else if (creatureX == adjCoordX + 1 && creatureY == adjCoordY)
		return Direction::LEFT;
	else if (creatureX == adjCoordX - 1 && creatureY == adjCoordY)
		return Direction::RIGHT;
	else
		return Direction::STAY;
}

