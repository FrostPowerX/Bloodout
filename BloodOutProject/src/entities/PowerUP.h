#ifndef POWER_UP
#define POWER_UP

#include "raylib.h"

struct PowerUp
{
	Rectangle rect;

	Color rectColor = WHITE;

	float addHeight = 0;
	float addSpeed = 0;
	int addBalls = 0;

	int toPlayer = -1;

	bool isActive = false;
};

PowerUp CreatePowerUp(Rectangle rect, Color rectColor, float heightPlus, float speedPlus, int ballsPlus);

void DrawPowerUp(PowerUp& pUp);

#endif // !POWER_UP
