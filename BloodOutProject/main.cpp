#include "sl.h"

void Input();
void Update();
void Draw();

void main()
{
	int screenWidth = 800;
	int screenHeight = 600;

	slWindow(screenWidth, screenHeight, "Cacho", 0);

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
