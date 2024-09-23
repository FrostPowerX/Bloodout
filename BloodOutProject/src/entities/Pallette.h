#ifndef PALLETE
#define PALLETE

#include "Color.h"
#include "Rectangle.h"
#include "Vector2.h"

struct Pallette
{
	Rectangle rect;
	Color color = WHITE;
	Color borderColor = WHITE;

	float direction = 0;
	float speed = 0;
};

Pallette CreatePallette(Vector2, Color, float width, float height, float speed);

void MovePallette(Pallette&, float dirX, float dirY);

void ChangeColorPallette(Pallette& pallette, Color color);

void ChangeWidthPall(Pallette& pallette, float width);

void ChangeHeightPall(Pallette& pallette, float height);

void ChangeSpeedPallette(Pallette& pallette, float speed);

void DrawPallette(Pallette& pallette);

#endif // !PALLETE

