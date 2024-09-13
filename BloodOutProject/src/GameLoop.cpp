#include <iostream>

#include "sl.h"
#include "GameLoop.h"
#include "utilities/Constants.h"

namespace gameLoop
{


	void Initialize();

	void Input();
	void Update();
	void Draw();

	void Play()
	{
		slWindow(screenWidth, screenHeight, "Cacho", false);
		slLoadFont("src/aerial.ttf");
		slSetFont(0, 15);


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

	}

	void Input()
	{

	}

	void Update()
	{

	}

	void Draw()
	{
		slRender();
	}
}