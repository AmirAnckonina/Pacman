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
		/*else if (userKey == STARTCOLORIZED)
			gameColorized = true;
		else
			gameColorized = false;*/
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
