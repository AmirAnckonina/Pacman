#include "Pacman.h"
#include "ThePacmanGame.h"

Pacman::Pacman(char _pacmanIcon) : Creature(_pacmanIcon) {}

void Pacman::move(GameBoard& board, const Position& pacmanPos)
{
	//Set potential new position to pacman, then check if it's valid.
	setCreatureNextPos(board);
	if (isCreaturePositionValid(board)) //So we should move the pacman //getDirection() != Direction::STAY && 
	{
		//print space in current position because soon the pacman will be moved.
		gotoxy(getCurrPos().getXPos(), getCurrPos().getYPos());
		if (board.getCellInBoard(getCurrPos()) != GameBoard::TUNNEL)
		{
			cout << GameBoard::SPACE;
		}
		else
		{
			if (ThePacmanGame::isGameColorized())
				setTextColor(board.getTunnelColor());

			cout << GameBoard::TUNNEL;
		}
	}
	else //In case not, please stay on the current position. + Rollback to nextPos
		resetAfterInvalidNextPos();
}


//Pacman::Pacman(Position _pacmanStartingPos, Position _pacmanCurrPos,
//	Position _pacmanNextPos, Direction _pacmanDirection ,Colors _pacmanColor, char _pacmanIcon)
//	: Creature(_pacmanStartingPos, _pacmanCurrPos, _pacmanNextPos, _pacmanDirection, _pacmanColor, _pacmanIcon) 
//{
//	livesLeft = 3;
//	score = 0;
//}

//Pacman::Pacman(Position _pacmanCurrPos, Position _pacmanNextPos, Direction _pacmanDirection = Direction::STAY
//	, Colors _pacmanColor = Colors::WHITE, char _pacmanIcon = '@')


void Pacman::initPacman(GameBoard& board)
{
	score = 0;
	livesLeft = 3;
	initCreature(board, '@');
}

//void Pacman::movePacman(GameBoard& board)
//{
//	//Set potential new position to pacman, then check if it's valid.
//	setCreatureNextPos(board);
//	if (isCreaturePositionValid(board)) //So we should move the pacman //getDirection() != Direction::STAY && 
//	{
//		//print space in current position because soon the pacman will be moved.
//		gotoxy(getCurrPos().getXPos(), getCurrPos().getYPos());
//		if (board.getCellInBoard(getCurrPos()) != GameBoard::TUNNEL)
//		{
//			cout << GameBoard::SPACE;
//		}
//		else
//		{
//			if (ThePacmanGame::isGameColorized())
//				setTextColor(board.getTunnelColor());
//
//			cout << GameBoard::TUNNEL;
//		}
//	}
//	else //In case not, please stay on the current position. + Rollback to nextPos
//		resetAfterInvalidNextPos();
//}

void Pacman::updateScore(GameBoard& board)
{
	//Collect score if breadCrumb placed in currPos
	/*if (board.getCellInBoard( getNextPos().getXPos(), getNextPos().getYPos() ) == GameBoard::BREADCRUMB)*/
	if (board.getCellInBoard(getNextPos()) == GameBoard::BREADCRUMB)
		score++;
}

Direction Pacman::convertKeyToDirection(char key) const
{
	//Key translation to Direction
	switch (key)
	{
	case 'w':
	case 'W':
		return Direction::UP;
	case 'x':
	case 'X':
		return Direction::DOWN;
	case 's':
	case 'S':
		return Direction::STAY;
	case 'd':
	case 'D':
		return Direction::RIGHT;
	case 'a':
	case 'A':
		return Direction::LEFT;
	default:
		return Direction::WRONG_KEY;
	}
}
