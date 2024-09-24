#ifndef POWER_UP
#define POWER_UP

#include "Rectangle.h"
#include "Color.h"

struct PowerUp
{
	Rectangle rect;

	Color rectColor = WHITE;

	float dirX = 0;
	float dirY = 0;

	float speed = 0;

	float addWidth = 0;
	float addSpeed = 0;
	float secondsInvulerable = 0;
	int addBalls = 0;

	int toPlayer = -1;

	bool isActive = false;
};

PowerUp CreatePowerUp(Rectangle rect, Color rectColor, float heightPlus, float speedPlus, float secondsInvulerable, int ballsPlus);

void MovePowerUp(PowerUp& p, float dirX, float dirY);

void DrawPowerUp(PowerUp& pUp);

#endif // !POWER_UP
