#include <iostream>

#include "sl.h"
#include "GameLoop.h"

#include "entities/Ball.h"
#include "entities/Pallette.h"

#include "utilities/Constants.h"
#include "utilities/Color.h"
#include "utilities/Utils.h"

namespace gameLoop
{
	Ball ball;
	Pallette player;

	void Initialize();

	void Input();
	void Update();
	void Draw();

	void Play()
	{
		slWindow(screenWidth, screenHeight, "Cacho", false);
		slLoadFont("src/aerial.ttf");
		slSetFont(0, 15);

		Initialize();

		while (!slShouldClose())
		{
			Input();
			Update();
			Draw();
		}

		slClose();
	}

	void Initialize()
	{
		ball = CreateBall(WHITE, 50, 50, 10, 500);

		player = CreatePallette(Vector2{ screenWidth / 2, 5 + 15 }, WHITE, 60.f, 15.f, 300.f);
	}

	void Input()
	{
		if (slGetKey('A'))
			MovePallette(player, -1, 0);
		else if (slGetKey('D'))
			MovePallette(player, 1, 0);

	}

	void Update()
	{
		MoveBall(ball);

		if (CheckBorderCollision(player.rect, screenWidth, 250, screenHeight, 0))
			SolveCollisionMap(player.rect, screenWidth, 250, screenHeight, 0);

		if (CheckBorderCollision(ball.cir, screenWidth, 250, screenHeight, 0))
			SolveCollisionMap(ball, screenWidth, 250, screenHeight, 0);

		if (CheckCollision(player.rect, ball.cir))
		{
			switch (SolveCollision(player.rect, ball.cir))
			{
			case HORIZONTAL:
				ball.dirX *= -1;
				break;

			case VERTICAL:
				ball.dirY *= -1;
				break;
			}
		}
	}

	void Draw()
	{
		DrawBall(ball);

		DrawPallette(player);

		slRender();
	}
}