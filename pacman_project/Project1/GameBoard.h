#pragma once
using namespace std;

#include <iostream>

class GameBoard
{
public:
    const char space = ' ';
    const char border = 254;
    const int boardSize = 30;

private:
    char board[30][30];
    //Color = ?

public:
    void initBoard();
    void printBoard();
};
