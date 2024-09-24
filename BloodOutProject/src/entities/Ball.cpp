#include "Ball.h"

#include "sl.h"
#include "Utils.h"

Ball CreateBall(Color color, float x, float y, float radius, float speed)
{
	Ball newBall = Ball();

	newBall.cir.x = x;
	newBall.cir.y = y;
	newBall.cir.radius = radius;

	newBall.color = color;
	newBall.speed = speed;

	float angle = ConvertGradesToRadian((GetRandomValue(450,1320) / 10.f));

	//float minAngleUp = ConvertGradesToRadian(45.f);
	//float maxAngleUp = ConvertGradesToRadian(132.f);

	//if (angle < minAngleUp && angle > maxAngleUp)
	//	angle = (angle > maxAngleUp) ? maxAngleUp : minAngleUp;

	newBall.dirX = cos(angle);
	newBall.dirY = sin(angle);

	NormalizeVector(newBall.dirX, newBall.dirY);

	newBall.playerId = -1;

	newBall.isActive = false;

	return newBall;
}

void TeleportBall(Ball& ball, float x, float y)
{
	ball.cir.x = x;
	ball.cir.y = y;
}

void MoveBall(Ball& ball)
{
	if (ball.freeze)
		return;

	if (ball.dirX > 1)
		ball.dirX = 1;
	else if (ball.dirX < -1)
		ball.dirX = -1;

	if (ball.dirY > 1)
		ball.dirY = 1;
	else if (ball.dirY < -1)
		ball.dirY = -1;

	ball.cir.x += ball.dirX * ball.speed * slGetDeltaTime();
	ball.cir.y += ball.dirY * ball.speed * slGetDeltaTime();
}

void ChangeColorBall(Ball& circle, Color newColor)
{
	circle.color = newColor;
}

void ChangeRadiusBall(Ball& circle, float newRadius)
{
	circle.cir.radius = newRadius;
}

void ChangeBallSpeed(Ball& ball, float speed)
{
	ball.speed = speed;
}

void SetFreeze(Ball& ball, bool freeze)
{
	ball.freeze = freeze;
}

void DrawBall(Ball& ball)
{
	SetForeColor(ball.color);
	slCircleFill(ball.cir.x, ball.cir.y, ball.cir.radius, 15);
	//slSetForeColor(0, 0, 0, 0);
}