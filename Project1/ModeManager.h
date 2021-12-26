#pragma once

#include "Utilities.h"
#include <fstream>
#include <filesystem>
#include "Directions.h"

using std::fstream;
namespace filesystem = std::filesystem;

class ModeManager
{
	fstream steps;
	fstream result;
	int sleepLength;

	//Get-set

	//Functions
	void writeStep(Direction dir);
};