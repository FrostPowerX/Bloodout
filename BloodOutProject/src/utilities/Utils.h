#ifndef UTILS
#define UTILS

#include <iostream>

#include "Circle.h"
#include "Rectangle.h"
#include "Ball.h"

#define PI 3.14159265359

enum TYPE_PENETRATION
{
	HORIZONTAL,
	VERTICAL,
	NONE
};

int GetRandomValue(int minValue, int maxValue);

float ConvertGradesToRadian(float grades);

bool CheckCollision(Rectangle r1, Rectangle r2);
bool CheckCollision(Rectangle r, Circle c);

bool CheckCollision(Circle c1, Circle c2);
bool CheckCollision(Circle c, Rectangle r);

bool CheckBorderCollision(Circle, float maxWidth, float minWidth, float maxHeight, float minHeight);
bool CheckBorderCollision(Rectangle, float maxWidth, float minWidth, float maxHeight, float minHeight);

TYPE_PENETRATION SolveCollision(Rectangle& r, Circle& c);
TYPE_PENETRATION SolveCollision(Circle& c, Rectangle& r);
TYPE_PENETRATION SolveCollision(Circle& entityA, Circle& entityB);

TYPE_PENETRATION SolveCollisionMap(Ball&, float maxWidth, float minWidth, float maxHeight, float minHeight);
TYPE_PENETRATION SolveCollisionMap(Rectangle&, float maxWidth, float minWidth, float maxHeight, float minHeight);

void NormalizeVector(float& x, float& y);

void BouncingAngle(Ball& ball, Rectangle& rect);

void BouncingBalls(Ball& c1, Ball& c2);

#endif // UTILS
