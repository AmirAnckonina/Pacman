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
	Pacman(char _pacmanIcon = Creature::PACMAN);
	virtual void move(GameBoard& board, const Position& pacmanPos = NULL) override;

	void updateLivesLeft() { livesLeft--; }
	void increaseLivesLeft() { livesLeft++; }
	void addFruitToScore(int fruitVal) { score += fruitVal; }
	void updateScore(GameBoard& board);
	void resetScoreAndLives() { score = 0; livesLeft = 3; }
	Direction convertKeyToDirection(char key) const;
	void setScore(int _score) { score = _score; }
	int getScore() const { return score; }
	int getLivesLeft() const { return livesLeft; }
};
