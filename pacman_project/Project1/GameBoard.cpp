#include "GameBoard.h"

void GameBoard::initBoard()
{
    int rowInd, colInd;

    for (rowInd = 0; rowInd < boardSize; rowInd++)
        board[rowInd][0] = border;
    for (colInd = 0; colInd < boardSize; colInd++)
        board[0][colInd] = border;
    for (rowInd = 0; rowInd < boardSize; rowInd++)
        board[rowInd][boardSize - 1] = border;
    for (colInd = 0 ; colInd < boardSize ; colInd++)
        board[boardSize - 1][colInd] = border;
    for (rowInd = 1; rowInd < boardSize - 1; rowInd++)
        for (colInd = 1; colInd < boardSize - 1; colInd++)
            board[rowInd][colInd] = space;
}

void GameBoard::printBorders()
{
    //gotoxy(1,1);
    for (int i = 0 ; i < 30 ; i++)
        cout << border ;
    for (int i = startingRow ; i <= endingRow ; i++)
        cout << border ;
    for (int i = startingRow ; i <= endingRow ; i++)
        cout << border ;
    for (int i = startingRow ; i <= endingRow ; i++)
        cout << border ;
    
}
