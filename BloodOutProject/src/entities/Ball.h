#ifndef BALL
#define BALL

#include "Color.h"
#include "Circle.h"

struct Ball
{
	Circle cir;
	Color color = WHITE;
	Color colorBorder = WHITE;

	float dirX = 0;
	float dirY = 0;

	float speed = 0;

	int playerId = -1;

	bool isActive = false;
};

Ball CreateBall(Color, float x, float y ,float radius, float speed);

void TeleportBall(Ball& ball, float x, float y);

void MoveBall(Ball& ball);

void ChangeColorBall(Ball& ball, Color color);

void ChangeRadiusBall(Ball& ball, float radius);

void ChangeBallSpeed(Ball& ball, float speed);

void DrawBall(Ball& ball);

#endif // !BALL
