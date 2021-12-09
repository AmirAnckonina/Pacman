#include "Ghost.h"
#include "ThePacmanGame.h"
//

Ghost::Ghost(Position _ghostStartingPos, Position _ghostCurrPos, Position _ghostNextPos, Direction _ghostDirection, Colors _ghostColor, char _ghostIcon)
	: Creature(_ghostStartingPos ,_ghostCurrPos, _ghostNextPos, _ghostDirection, _ghostColor, _ghostIcon) {}

void Ghost::initGhost(GameBoard& board)
{
	//Startegy
	initCreature(board, '$');
}

/*void Ghost::setGhostPosition(int xCoord, int yCoord)
{
	currPos.setXPos(xCoord);
	currPos.setYPos(yCoord);
	nextPos = currPos;
}*/

void Ghost::moveGhost(GameBoard& board)
{
	bool isValid = false;
	while (!isValid)
	{
		//Set potential new position to ghost, then check if it's valid.
		generateRandomDirection();
		setCreatureNextPos(board);
		isValid = isCreaturePositionValid(board);
		if (!isValid) //Rollback, before starting the loop again.
			resetNextPos();
	}

	//The ghost printed and we want the print the cell as it were before.
	gotoxy(getCurrPos().getXPos(), getCurrPos().getYPos());
	if (board.getCellInBoard(getCurrPos()) == GameBoard::BREADCRUMB)
	{
		if (ThePacmanGame::isGameColorized())
			setTextColor(board.getBreadcrumbColor());
		cout << GameBoard::BREADCRUMB;
	}
	else
		cout << GameBoard::SPACE;
}

/*void Ghost::printGhost() const
{
	gotoxy(currPos.getXPos(), currPos.getYPos());
	if (ThePacmanGame::isGameColorized())
		setTextColor(ghostColor);
	cout << GHOST;
}*/

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

/*void Ghost::smartGhostMove(GameBoard& board)
{

	{
		// Visited vector to so that
		// a vertex is not visited more than once
		// Initializing the vector to false as no
		// vertex is visited at the beginning
		vector<bool> visited(adj.size(), false);
		vector<int> q;
		q.push_back(start);

		// Set source as visited
		visited[start] = true;

		int vis;
		while (!q.empty()) {
			vis = q[0];

			// Print the current node
			cout << vis << " ";
			q.erase(q.begin());

			// For every adjacent vertex to the current vertex
			for (int i = 0; i < adj[vis].size(); i++) {
				if (adj[vis][i] == 1 && (!visited[i])) {

					// Push the adjacent node to the queue
					q.push_back(i);

					// Set
					visited[i] = true;
				}
			}
		}
	}







}*/

