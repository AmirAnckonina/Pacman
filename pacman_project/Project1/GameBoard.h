#pragma once
using namespace std;

#include <iostream>
#include <cstdlib>
#include <time.h>

const int ROWMAX = 20;
const int COLMAX = 80;
const char SPACE = ' ';
const char BORDER_VERTICAL = 219;
const char BORDER_HORIZONTAL = 254;

class GameBoard
{
private:
    char _board[ROWMAX][COLMAX];
    //Color = ?

public:
    void initBoard();
    void initInnerWalls(char board[][COLMAX]);
    void printBoard();
};
