#pragma once

#include "Utilities.h"
#include "Directions.h"
#include "Position.h"
#include "GameBoard.h"
#include "Creature.h"

using std::cout;
using std::endl;

class Pacman : public Creature
{
private:
	int livesLeft = 3;
	int score = 0;

public:
	Pacman() {};
	Pacman(Position _pacmanStartingPos, Position _pacmanCurrPos, Position _pacmanNextPos,
		Direction _pacmanDirection = Direction::STAY, Colors _pacmanColor = Colors::WHITE, char _pacmanIcon = '@');
	void initPacman(GameBoard& board);
	void movePacman(GameBoard& board);
	void updateLivesLeft() { livesLeft--; }
	void updateScore(GameBoard& board);

	//Get-Set Functions
	Direction convertKeyToDirection(char key) const;
	int getScore() const { return score; }
	int getLivesLeft() const { return livesLeft; }
};
