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

	void addFruitToScore(int fruitVal) { score += fruitVal; }
	void initPacman(GameBoard& board);
	//void movePacman(GameBoard& board);
	void updateLivesLeft() { livesLeft--; }
	void increaseLivesLeft() { livesLeft++; }
	void updateScore(GameBoard& board);
	void setScore(int _score) { score = _score; }



	//Get-Set Functions
	Direction convertKeyToDirection(char key) const;
	int getScore() const { return score; }
	int getLivesLeft() const { return livesLeft; }

};
