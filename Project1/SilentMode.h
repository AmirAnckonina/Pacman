#pragma once

#include "ThePacmanGame.h"
#include <fstream>


using std::ifstream;

class SilentMode : public ThePacmanGame
{
protected:


public:
	virtual void runAllSessions() override;
	virtual void runSingleSession(size_t& totalNumOfScreens) override;
};