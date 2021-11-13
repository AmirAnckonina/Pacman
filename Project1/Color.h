#pragma once

#include <Windows.h>


class Color
{
private:
	int color = 0;
	enum colorsOptions
	{
		WHITE = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		YELLOW = 5,
		BLACK = 6
	};

public:
	void setTextColor(int c);
};