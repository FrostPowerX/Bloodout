#include "PowerUP.h"

#include "sl.h"
#include "Constants.h"

PowerUp CreatePowerUp(Rectangle rect, Color rectColor, float heightPlus, float speedPlus, float secondsInvulnerable, int ballsPlus)
{
	PowerUp newPowerUp;

	newPowerUp.rect = rect;
	newPowerUp.rectColor = rectColor;
	newPowerUp.addWidth = heightPlus;
	newPowerUp.addSpeed = speedPlus;
	newPowerUp.addBalls = ballsPlus;
	newPowerUp.secondsInvulerable = secondsInvulnerable;

	newPowerUp.toPlayer = -1;
	newPowerUp.isActive = false;

	return newPowerUp;
}

void MovePowerUp(PowerUp& p, float dirX, float dirY)
{
	if (dirX > 1)
		dirX = 1;
	else if (dirX < -1)
		dirX = -1;

	if (dirY > 1)
		dirY = 1;
	else if (dirY < -1)
		dirY = -1;

	p.rect.x += dirX * p.speed * slGetDeltaTime();

	p.rect.y += dirY * p.speed * slGetDeltaTime();
}

void DrawPowerUp(PowerUp& p)
{
	SetForeColor(p.rectColor);
	slRectangleFill(p.rect.x, p.rect.y, p.rect.width, p.rect.height);
}
