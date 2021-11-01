#pragma once
using namespace std;

#include <iostream>

class GameBoard
{
private:
    const int startingRow = 1;
    const int endingRow = 30;
    const int startingCol = 1;
    const int endingCol = 30;
    char border = '|';
    
    //Color = ?
public:
    void printBorders();
};
