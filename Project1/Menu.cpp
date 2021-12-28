#include "Menu.h"
#include "ThePacmanGame.h"
#include "Creature.h"

void Menu::pressAnyKey()
{
	cout << "Press any key to continue..." << endl;
	userKey = _getch();
	userKey = 0;
	clearScreen();
}

void Menu::entryMenu()
{
	static bool firstTimeMenu = true;
	clearInput();
	pressAnyKey();
	if (firstTimeMenu)
	{
		gotoxy(0, 0);
		cout << "Welcome to Pacman game!" << endl;
		Sleep(2000);
		firstTimeMenu = false;
		clearScreen();
	}

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
	//cout << "Welcome to Pacman game!" << endl;
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






int Menu::getFirstBoardChoice(GameBoard& board)
{
	bool boardChoosed = false;

	while (!boardChoosed)
	{
		size_t numOfTemplates = board.getNumOfTemplates();
		printBoardsSelectionMenu(board, numOfTemplates);
		userKey = _getch();
		userKey -= '0';
		boardChoosed = userChoosedBoard(numOfTemplates);
	}
	int userChosenTemplate = userKey;
	userKey = 0;
	clearScreen();
	return userChosenTemplate;
}

bool Menu::userChoosedBoard(size_t& boardTemplatesSize) const
{
	if (userKey >= 0 && userKey < boardTemplatesSize)
		return true;

	return false;
}

void Menu::printBoardsSelectionMenu(GameBoard& board, size_t& numOfTemplates) const
{
	gotoxy(0, 0);
	cout << "Please choose your starting board:" << endl;
	for (int templateInd = 0; templateInd < numOfTemplates; templateInd++)
	{
		cout << "Press (" << templateInd << ") for " << board.getScreenTemplateName(templateInd) << endl;
	}
}

bool Menu::userChoosedToStart() const
{
	if (userKey == START || userKey == STARTCOLORIZED || userKey == EXIT)
		return true;
	else
		return false;
}



int Menu::getGameDifficulty()
{
	bool levelChoosed = false;

	while (!levelChoosed)
	{
		printLevelsMenu();
		userKey = _getch();
		levelChoosed = userChoosedDifficulty();
	}
	clearScreen();
	return userKey - '0';
}

bool Menu::userChoosedDifficulty() const
{
	switch (userKey)
	{
	case BEGINNER:
	case AMATEUR:
	case PROFESSIONAL:
		return true;
	default:
		return false;
	}
}

void Menu::printLevelsMenu()
{
	gotoxy(0, 0);
	cout << "Please choose game difficuly level" << endl;
	cout << "Press (1) for Begginer" << endl;
	cout << "Press (2) to for Amateur" << endl;
	cout << "Press (3) for Professional" << endl;
}












