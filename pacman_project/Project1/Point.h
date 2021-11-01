#pragma once
using namespace std;

#include "Windows.h"

class Point
{
private:
    int _x = 1 , _y = 1;
public:
    void printPoint(int x, int y);
    void gotoxy(int x, int y);
};
