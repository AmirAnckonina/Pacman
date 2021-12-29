#include <iostream>
#include "RunMode.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	RunMode newGame;
	newGame.assignGameModeAndRun(argv[1]);
	return 0;
}


