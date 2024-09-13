#include "PowerUP.h"
#include "..\utilities\Constants.h"

PowerUp CreatePowerUp(Rectangle rect, Color rectColor, float heightPlus, float speedPlus, int ballsPlus)
{
	PowerUp newPowerUp;

	newPowerUp.rect = rect;
	newPowerUp.rectColor = rectColor;
	newPowerUp.addHeight = heightPlus;
	newPowerUp.addSpeed = speedPlus;
	newPowerUp.addBalls = ballsPlus;

	newPowerUp.toPlayer = -1;
	newPowerUp.isActive = false;

	return newPowerUp;
}

void DrawPowerUp(PowerUp& pUp)
{
	Vector3 pos;
	pos.x = pUp.rect.x + (pUp.rect.width / 2) - (screenWidth / 2);
	pos.y = 10;
	pos.z = pUp.rect.y + (pUp.rect.height / 2) - (screenHeight / 2);

	DrawCube(pos, pUp.rect.width, 15, pUp.rect.height, pUp.rectColor);
	//DrawCubeWires(pos, pUp.rect.width, 15, pUp.rect.height, BLUE);
	//DrawRectangleRec(pUp.rect, pUp.rectColor);
}
