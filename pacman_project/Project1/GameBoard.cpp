#include "GameBoard.h"

void GameBoard::printBorders()
{
    //gotoxy(1,1);
    for (int i = startingRow ; i <= endingRow ; i++)
        cout << border ;
    for (int i = startingRow ; i <= endingRow ; i++)
        cout << border ;
    for (int i = startingRow ; i <= endingRow ; i++)
        cout << border ;
    for (int i = startingRow ; i <= endingRow ; i++)
        cout << border ;
    //check if it works
}
