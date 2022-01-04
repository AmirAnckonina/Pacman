#pragma once

#include "SilentMode.h"
using std::vector;
using std::ifstream;
using std::cin;


class LoadMode : public SilentMode
{
public:
	virtual void run() override;
	virtual void executeSleepBetweenSessions() override;
};