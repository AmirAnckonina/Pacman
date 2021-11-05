#pragma once
using namespace std;

#include <iostream>
#include <cstdlib>
#include <time.h>

const int ROWMAX = 25;
const int COLMAX = 80;
const char SPACE = ' ';
const char BORDER = 219;
const char BREADCRUMB = '*';

class GameBoard
{
private:
    char** _board;
    //Color = ?

public:
    void initBoard();
    void allocateBoard();
    void initOuterBorders();
    void initInnerWalls();
    void initBreadcrumbs();
    char** getBoard();
    void printBoard();
};
