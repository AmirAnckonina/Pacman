#pragma once

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
	ThePacmanGame* game;

public:
	void assignGameModeAndRun(const char* _runModeType);
};