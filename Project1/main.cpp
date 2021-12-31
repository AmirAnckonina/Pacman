#include <iostream>
#include "RunMode.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	RunMode newGame(argc, argv);
	newGame.assignGameModeAndRun();
	return 0;
}


