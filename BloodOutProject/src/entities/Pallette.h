#ifndef PALLETE
#define PALLETE

#include "raylib.h"

struct Pallette
{
	Rectangle rect;
	Color color = WHITE;
	Color borderColor = WHITE;

	float direction = 0;
	float speed = 0;
};

Pallette CreatePallette(Vector2, Color, float width, float height, float speed);

void MovePallette(Pallette&, float);

void ChangeColorPallette(Pallette&, Color);

void ChangeWidthPall(Pallette&, float);

void ChangeHeightPall(Pallette&, float);

void ChangeSpeedPallette(Pallette&, float);

void DrawPallette(Pallette&);

#endif // !PALLETE

