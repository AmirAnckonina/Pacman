#include "Menu.h"
#include "ThePacmanGame.h"
#include "Creature.h"


void Menu::entryMenu()
{
	clearInput();
	cout << "Press any key to enter the game menu..." << endl;
	userKey = _getch();
	userKey = 0;
	clearScreen();

	while (!userChoosedToStart())
	{
		printMenu();
		userKey = _getch();
		if (userKey == INSTRUCTIONS)
			printInstructions();
	}
	clearScreen();
}

void Menu::printMenu() const
{
	gotoxy(0, 0);
	cout << "Welcome to Pacman game!" << endl;
	cout << "Press (1) to Start without colors" << endl;
	cout << "Press (2) to Start with colors" << endl;
	cout << "Press (8) for Instructions" << endl;
	cout << "press (9) to exit" << endl;
}

void Menu::printInstructions()
{
	clearScreen();

	cout << "Welcome to Pacman game!" << endl;
	cout << "Pac - MAN has 3 life in this game." << endl;
	cout << "Pac - MAN will gain points by collecting all the breadcrumbs in the maze." << endl;
	cout << "You should avoid any interactions with the ghosts. Otherwise, you will be eaten and lose lives." << endl;
	cout << "To win the game you should eat ALL the breadcrumbs" << endl;
	cout << endl;
	cout << endl;
	cout << "Keys instruction: " << endl;
	cout << "Move UP: press w or W " << endl;
	cout << "Move DOWN: press x or X" << endl;
	cout << "Move LEFT: press a or A" << endl;
	cout << "Move RIGHT: press d or D" << endl;
	cout << "To STAY in your position: press s or S" << endl;
	cout << "Good Luck!" << endl;
	cout << endl;
	cout << "Press ESC to return the main menu." << endl;

	while (userKey != ESC)
		userKey = _getch();

	clearScreen();
	userKey = 0;
}

bool Menu::userChoosedToStart() const
{
	if (userKey == START || userKey == STARTCOLORIZED || userKey == EXIT)
		return true;
	else
		return false;
}

void Menu::initDetailsArea(GameBoard& board)
{  
	detailsColor = Colors::WHITE;
	legendAreaPos = board.collectStartingPos(GameBoard::LEGEND);
	int legendStartingRow = legendAreaPos.getYPos();
	int legendStartingCol =legendAreaPos.getXPos();

	for (int rowInd = legendStartingRow; rowInd < legendStartingRow + 3; rowInd++)
	{
		for (int colInd = legendStartingCol; colInd < legendStartingCol + 20; colInd++)
		{
			board.setCellInBoard(colInd, rowInd, GameBoard::LEGEND);
		}
	}
	clearLegendArea();
}

void Menu::pauseGame(int lives) const
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

void Menu::singlePrintScore(int score) const
{
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 2);
	for (int i = 0; i < 20; i++)
		cout << GameBoard::SPACE;
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 2);
	cout << " The score is : " << score;
}

void Menu::printLives(int lives) const
{
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 1);
	cout << "   Lives Left: " << lives << "    ";
}

void Menu::printResult(bool playerWon, int score, Colors pacmanColor, Colors ghostColor) const
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
			cout << "  Congratulations  " << endl;
			cout << "      You Won!      ";
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
			cout << "    GAME OVER!!!    " << endl;
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
	cout << "Your final score is:" << endl;  
	gotoxy(legendAreaPos.getXPos() + 8, legendAreaPos.getYPos() + 2);
	cout << score;
	Sleep(2500);

	clearLegendArea();

	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos() + 1);
	cout << " Thanks for playing " << endl;
	Sleep(3000);
}

void Menu::printGameName() const
{
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(legendAreaPos.getXPos(), legendAreaPos.getYPos());
	cout << "   P A C - M A N    ";
}

void Menu::printRSG() const
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

void Menu::clearLegendArea() const
{
	for (int rowInd = 0; rowInd < 3; rowInd++)
	{
		gotoxy(legendAreaPos.getXPos() , legendAreaPos.getYPos() + rowInd);
		for (int colInd = 0; colInd < 20; colInd++)
		{
			cout << GameBoard::SPACE;
		}
	}
}

//Pacman animation at the end
void Menu::printPacmanAllAround(Colors pacmanColor) const
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
void Menu::printGhostsAllAround(Colors ghostColor) const
{
	//int x1 = 21, y1 = 11, x2 = 59, y2 = 13;
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

