#include "GameBoard.h"

void GameBoard::initBoard()
{
    int rowInd, colInd;

    for (rowInd = 0; rowInd < ROWMAX ; rowInd++)
        _board[rowInd][0] = BORDER_VERTICAL;

    for (colInd = 0; colInd < COLMAX ; colInd++)
        _board[0][colInd] = BORDER_HORIZONTAL;
    
    for (rowInd = 1; rowInd < ROWMAX; rowInd++)
        _board[rowInd][COLMAX - 1] = BORDER_VERTICAL;

    for (colInd = 0 ; colInd < COLMAX ; colInd++)
        _board[ROWMAX - 1][colInd] = BORDER_HORIZONTAL;
    
    for (rowInd = 1; rowInd < ROWMAX - 1; rowInd++)
        for (colInd = 1; colInd < COLMAX - 1; colInd++)
            _board[rowInd][colInd] = SPACE; 

    initInnerWalls(_board);
}

void GameBoard::initInnerWalls(char board[][COLMAX])
{
    int rowInd, colInd, k;
   
    for (rowInd = 0 ,colInd = 0 ; rowInd < ROWMAX && colInd < COLMAX ; rowInd += 2)
    {
        colInd = rowInd * 2;
        for (k = 0; k < 6; k++)
            board[rowInd][colInd++] = BORDER_HORIZONTAL;
    }



}
void GameBoard::printBoard()
{
    //gotoxy(1,1);
    int rowInd, colInd;
    for (rowInd = 0; rowInd < ROWMAX; rowInd++)
    {
        for (colInd = 0; colInd < COLMAX ; colInd++)
            cout << _board[rowInd][colInd];
        
        cout << endl;
    }

}