#ifndef BALL
#define BALL

#include <iostream>

#include "sl.h"
#include "..\utilities\Circle.h"

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

void TeleportBall(Ball&, float, float);

void MoveBall(Ball&);

void ChangeColorBall(Ball&, Color);

void ChangeRadiusBall(Ball&, float);

void ChangeBallSpeed(Ball&, float);

void DrawBall(Ball&);

#endif // !BALL
