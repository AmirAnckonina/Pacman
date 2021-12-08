#include "Menu.h"
#include "Menu.h"
#include "ThePacmanGame.h"


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
	legendAreaPos = game_board.collectStartingPos('&');
}

void Menu::pauseGame() const
{
	char key;

	gotoxy(24, 11);
	if (gameColorized)
		setTextColor(detailsColor);
	cout << "Game paused, press ESC to continue";
	key = _getch();

	while (key != Menu::ESC)
		key = _getch();

	gotoxy(21, 11);
	cout << "                    " << endl;//remove pause message
	printGameName();
}

void Menu::singlePrintScore(int score) const
{
	gotoxy(21, 13);
	cout << "                    " << endl;
	if (gameColorized)
		setTextColor(detailsColor);
	gotoxy(32, 13);
	cout << "The score is = " << score;
}

void Menu::printLives(int lives) const
{
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(34, 12);
	cout << "Lives Left: " << lives;
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
			gotoxy(27, 12);
			cout << "Congratulations, You WON!" << endl;
			Sleep(750);
			gotoxy(21, 12);
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
			gotoxy(33, 12);
			cout << "GAME OVER!!!!" << endl;
			Sleep(500);
			clearLegendArea();
			Sleep(500);
		}
		printGhostsAllAround(ghostColor);
	}
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	clearLegendArea();
	gotoxy(27, 12);
	cout << "your final score is: " << score << endl;
	Sleep(2500);
	clearLegendArea();
	gotoxy(30, 12);
	cout << "Thanks for playing!" << endl;
	Sleep(3000);
}

void Menu::printGameName() const
{
	if (ThePacmanGame::isGameColorized())
		setTextColor(detailsColor);
	gotoxy(29, 11);
	cout << "  P  A  C  -  M  A  N  ";
}

void Menu::printRSG() const
{
	if (ThePacmanGame::isGameColorized()) setTextColor(detailsColor);

	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(37, 11);
	cout << "Ready,";
	Sleep(1200);
	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(38, 11);
	cout << "Set,";
	Sleep(1200);
	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(38, 11);
	cout << "GO!";
	Sleep(750);
	gotoxy(21, 11);
	cout << "                                       " << endl;
}

void Menu::clearLegendArea() const
{
	gotoxy(21, 11);
	cout << "                                       " << endl;
	gotoxy(21, 12);
	cout << "                                       " << endl;
	gotoxy(21, 13);
	cout << "                                       " << endl;
}

//Pacman animation at the end
void Menu::printPacmanAllAround(Colors pacmanColor) const
{
	int x = 21, y = 11;
	if (gameColorized) setTextColor(pacmanColor);
	while (x <= 59)
	{
		gotoxy(x++, y);
		cout << Pacman::PACMAN;
		Sleep(5);
	}
	x--;
	y++;
	while (x >= 21)
	{
		gotoxy(x--, y);
		cout << Pacman::PACMAN;
		Sleep(5);
	}
	x++;
	y++;
	while (x <= 59)
	{
		gotoxy(x++, y);
		cout << Pacman::PACMAN;
		Sleep(5);
	}

	Sleep(1500);
}

//Ghost Animation at the end
void Menu::printGhostsAllAround(Colors ghostColor) const
{
	int x1 = 21, y1 = 11, x2 = 59, y2 = 13;
	if (ThePacmanGame::isGameColorized()) setTextColor(ghostColor);
	while (x1 <= 59 && x2 >= 21)
	{
		gotoxy(x1++, y1);
		cout << Icon::GHOST;
		gotoxy(x2--, y2);
		cout << Icon::GHOST;
		Sleep(5);
	}
	x1--;
	y1++;
	x2++;
	y2--;
	while (x2 <= x1)
	{
		gotoxy(x1--, y1);
		cout << Icon::GHOST;
		gotoxy(x2++, y2);
		cout << Icon::GHOST;
		Sleep(5);
	}
	Sleep(1500);
}

