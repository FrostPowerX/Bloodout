#include <iostream>

#include "sl.h"
#include "GameLoop.h"
#include "utilities/Constants.h"
#include "entities/Ball.h"
#include "utilities/Color.h"
#include "utilities/Utils.h"

namespace gameLoop
{
	Ball ball;

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
	}

	void Input()
	{

	}

	void Update()
	{
		MoveBall(ball);

		if (CheckBorderCollision(ball.cir, screenWidth, 0, screenHeight, 0))
			SolveCollisionMap(ball, screenWidth, 0, screenHeight, 0);
	}

	void Draw()
	{
		DrawBall(ball);

		slRender();
	}
}