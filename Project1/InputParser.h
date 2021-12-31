#pragma once
#include "Utilities.h"

class InputParser 
{
private:
    std::vector <std::string> tokens;
public:
    InputParser(int& argc, char** argv);
    const std::string& getCmdOption(const std::string& option) const;
    bool cmdOptionExists(const std::string& option) const; 
};

