#pragma once
using namespace std;

#include <iostream>

class ThePacmanGame
{
private:
    enum {ESC = 27};

public:
    void initGame();
    void runGame();
};