#pragma once
#include "InputParser.h"

class ThePacmanGame;
class SimpleMode;
class SaveMode;
class SilentMode;
class LoadMode;

class RunMode
{
public:
	enum RunModeType {SIMPLE, SAVE, LOAD, SILENT};

private:
	InputParser input;
	ThePacmanGame* game;

public:
	RunMode(int& _argc, char** _argv) : input(_argc, _argv), game(nullptr) {}
	~RunMode();
	void assignGameModeAndRun();
};