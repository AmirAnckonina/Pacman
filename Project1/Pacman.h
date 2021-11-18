#pragma once

#include "Utilities.h"
#include "Position.h"
#include "GameBoard.h"

using std::cout;
using std::endl;
class Pacman
{

private:
	const char pacmanFigure = PACMAN;
	gameColors pacColor = gameColors::WHITE;
	Position currPos, nextPos;
	Direction pacmanDirection = Direction::STAY; 
	int livesLeft = 3;
	int score = 0;

public:
	
	Position getCurrPos() const { return currPos; }
	Direction getDirection (char key) const;
	int getScore() const { return score; }
	int getLivesLeft() const { return livesLeft; }
	gameColors getPacColor() const { return pacColor; }
	void printPacman() const;

	void setDirection(Direction dir);
	void setPacColor(gameColors color = gameColors::WHITE) { pacColor = color; }
	void setPacmanPosition();
	void updateLivesLeft() { livesLeft--; }
	void updatePos() { currPos = nextPos; };
	void updateScore(GameBoard& board);

	void initPacman(); 
	void movePacman(GameBoard& board);
};
