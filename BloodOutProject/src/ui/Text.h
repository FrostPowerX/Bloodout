#ifndef TEXT
#define TEXT

#include <iostream>

#include "Vector2.h"
#include "Color.h"

struct Text
{
	Vector2 position;
	std::string text;

	int font = 0;

	Color color;
};

Text CreateText(std::string, int x, int y, int font, Color color);

void DrawText(Text text);

#endif // !TEXT
