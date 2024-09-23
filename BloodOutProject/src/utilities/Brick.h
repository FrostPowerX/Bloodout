#ifndef BRICK
#define BRICK

#include "HealthSystem.h"
#include "Rectangle.h"
#include "Vector2.h"
#include "Color.h"

struct Brick
{
	Rectangle rect;
	HealthSystem health;

	Color colorT1;
	Color colorT2;
	Color colorT3;

	bool isActive;
};

Brick CreateBrick(Rectangle rect, float health, Color cT1, Color cT2, Color cT3);

void SetPosition(Brick& b, Vector2 newPos);

void DrawBrick(Brick b);

#endif // !BRICK
