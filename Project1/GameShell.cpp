#include "GameShell.h"
#include "ThePacmanGame.h"
#include "Creature.h"


void GameShell::betweenScreensProcedure(GameBoard& board, int currTemplate, int lastGamePacmanScore, bool playerWon)
{
	if (board.isBoardValid())
	{
		updateTotalPlayerScore(lastGamePacmanScore);
		size_t numOfTemplates = board.getNumOfTemplates();

		if (playerWon != false)
			printDataAfterSession(board, currTemplate);
		else
			printDataAfterLosing(board, currTemplate);
	}
	else if (currTemplate == board.getNumOfTemplates() - 1)
	{
		printDataAfterSession(board, currTemplate);
	}
}
void GameShell::pauseGame(int lives) const
{
	char key;
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	cout << "    Game paused.    ";
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 1);
	cout << "  Please press ESC  ";
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 2);
	cout << "    to continue     ";
	key = _getch();

	while (key != Menu::ESC)
		key = _getch();

	clearLegendArea();
	printLives(lives);
	printGameName();
}
void GameShell::printDataAfterLosing(GameBoard& board, int& currTemplate) const
{
	cout << "We're Sorry, GAME OVER." << endl;
	cout << "You lost on screen '" << board.getScreenTemplateName(currTemplate) << "'" << endl;
	cout << "Your total score is: " << totalPlayerScore << endl;
	cout << "Maybe next time!" << endl;
	Sleep(5000);
	clearScreen();
}
void GameShell::printDataAfterSession(GameBoard& board, int& currTemplate) const
{
	if (board.isValidBoard())
	{
		cout << "You're doing well so far! You've just completed screen: " << endl;
		cout << "'" << board.getScreenTemplateName(currTemplate) << "'" << endl;
		Sleep(2000);
		cout << "The total score you've achieved: " << totalPlayerScore << endl;
		Sleep(2000);
		if (currTemplate < (board.getNumOfTemplates() - 1))
			cout << "Let's move to the next board, keep going playa!" << endl;
		else
			cout << "All boards completed successfully! You Won!!!" << endl;
		Sleep(5000);
		clearScreen();
	}
	else if (currTemplate == board.getNumOfTemplates() - 1 && !(board.isValidBoard()))
	{
		cout << "The total score you've achieved: " << totalPlayerScore << endl;
		Sleep(2000);
		cout << "All boards completed successfully! You Won!!!" << endl;
		Sleep(5000);
		clearScreen();
	}

}
void GameShell::printAllLegend(int score, int lives) const
{
	printGameName();
	printLives(lives);
	singlePrintScore(score);
}

void GameShell::initDetailsArea(GameBoard& board)
{
	detailsColor = Colors::WHITE;
	legendAreaPos = board.collectStartingPos(GameBoard::LEGEND);
	setLegendAreaChars(board);
	clearLegendArea();
}

void GameShell::setLegendAreaChars(GameBoard& board)
{
	int legendStartingRow = legendAreaPos.getYPos();
	int legendStartingCol = legendAreaPos.getXPos();
	for (int rowInd = legendStartingRow; rowInd < legendStartingRow + 3; rowInd++)
	{
		for (int colInd = legendStartingCol; colInd < legendStartingCol + 20; colInd++)
		{
			board.setCellInBoard(colInd, rowInd, GameBoard::LEGEND);
		}
	}
}

void GameShell::singlePrintScore(int score) const
{
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 2);
	for (int i = 0; i < 20; i++)
		cout << GameBoard::SPACE;
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 2);
	cout << "  The score is: " << score;
}

void GameShell::printLives(int lives) const
{
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 1);
	cout << "   Lives Left: " << lives << "    ";
}

void GameShell::printResult(bool playerWon, int score, Colors pacmanColor, Colors ghostColor) const
{
	Sleep(750);
	clearLegendArea();
	if (playerWon == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (ThePacmanGame::isGameColorized())
				setTextColor(pacmanColor);
			gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
			cout << "  Congratulations  ";
			gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 1);
			cout << "  Board Completed! ";
			Sleep(750);
			clearLegendArea();
			Sleep(750);
		}
		printPacmanAllAround(pacmanColor);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (ThePacmanGame::isGameColorized())
				setTextColor(ghostColor);

			gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
			cout << "    GAME OVER!!!   " << endl;
			Sleep(500);
			clearLegendArea();
			Sleep(500);
		}
		printGhostsAllAround(ghostColor);
	}

	clearLegendArea();

	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);

	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 1);
	cout << "    Final Score:    " << endl;
	gotoxy(legendAreaPos.getXPos() + 8, legendAreaPos.getYPos() + 2);
	cout << score;
	Sleep(2500);

	clearLegendArea();

	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 1);
	cout << "@$@$@$@$@$@$@$@$@$@$";
	Sleep(2000);
}

void GameShell::printGameName() const
{
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	cout << "   P A C - M A N    ";
}

void GameShell::printRSG() const
{
	if (ThePacmanGame::isGameColorized()) setTextColor(detailsColor);

	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	for (int i = 0; i < 20; i++)
		cout << GameBoard::SPACE;
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	cout << "       Ready,       ";
	Sleep(1200);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	for (int i = 0; i < 20; i++)
		cout << GameBoard::SPACE;
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	cout << "        Set,        ";
	Sleep(1200);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	for (int i = 0; i < 20; i++)
		cout << GameBoard::SPACE;
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	cout << "        GO !        ";
	Sleep(750);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	for (int i = 0; i < 20; i++)
		cout << GameBoard::SPACE;
}
void GameShell::clearLegendArea() const
{
	for (int rowInd = 0; rowInd < 3; rowInd++)
	{
		gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + rowInd);
		for (int colInd = 0; colInd < 20; colInd++)
		{
			cout << GameBoard::SPACE;
		}
	}
}
//Pacman animation at the end
void GameShell::printPacmanAllAround(Colors pacmanColor) const
{
	int x = legendAreaPos.getXPos();
	int y = legendAreaPos.getYPos();
	int endX = x + 19;
	int endY = y + 2;
	if (ThePacmanGame::isGameColorized()) setTextColor(pacmanColor);
	while (x <= endX)
	{
		gotoxy(x++, y);
		cout << Creature::PACMAN;
		Sleep(5);
	}
	x--;
	y++;
	endX = x - 19;
	while (x >= endX)
	{
		gotoxy(x--, y);
		cout << Creature::PACMAN;
		Sleep(5);
	}
	x++;
	y++;
	endX = x + 19;
	while (x <= endX)
	{
		gotoxy(x++, y);
		cout << Creature::PACMAN;
		Sleep(5);
	}

	Sleep(1500);
}

//Ghost Animation at the end
void GameShell::printGhostsAllAround(Colors ghostColor) const
{
	int x1 = legendAreaPos.getXPos();
	int endX1 = x1 + 19;
	int x2 = x1 + 19;
	int endX2 = x1;
	int y1 = legendAreaPos.getYPos();
	int y2 = y1 + 2;
	if (ThePacmanGame::isGameColorized()) setTextColor(ghostColor);
	while (x1 <= endX1 && x2 >= endX2)
	{
		gotoxy(x1++, y1);
		cout << Creature::GHOST;
		gotoxy(x2--, y2);
		cout << Creature::GHOST;
		Sleep(5);
	}
	x1--;
	y1++;
	x2++;
	y2--;
	while (x2 <= x1)
	{
		gotoxy(x1--, y1);
		cout << Creature::GHOST;
		gotoxy(x2++, y2);
		cout << Creature::GHOST;
		Sleep(5);
	}
	Sleep(1500);
}

