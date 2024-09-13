#ifndef TEXT
#define TEXT

#include <iostream>
#include "raylib.h"

struct Text
{
	Vector2 position;
	std::string text;

	int font;

	Color color;
};

Text CreateText(std::string, int x, int y, int font, Color color);

void DrawText(Text text);

#endif // !TEXT
