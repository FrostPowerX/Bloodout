#include <iostream>

#include "sl.h"

void Input();
void Update();
void Draw();

void main()
{
	int screenWidth = 800;
	int screenHeight = 600;

	float delta = 0;

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
