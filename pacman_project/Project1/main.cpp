#include <iostream>
using namespace std;

#include "ThePacmanGame.h"
#include "GameBoard.h" //should be to ThePacmanGame.h

int main()
{
    //CHANGE_TESTGIT
    /*ThePacmanGame game;
    game.initGame();
    game.runGame();*/

    GameBoard board;
    board.initBoard();
    board.printBoard();
    return 0;
}