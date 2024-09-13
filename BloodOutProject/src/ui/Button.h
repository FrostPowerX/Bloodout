#ifndef BUTTON
#define BUTTON

#include <string>

#include "raylib.h"

struct Button
{
	Rectangle rect;

	std::string text;

	Vector2 textPosition;

	Color normalColor = WHITE;
	Color onMouseTopColor = WHITE;
	Color pressedColor = WHITE;

	Color textColor = WHITE;

	int fontSize = 0;

	bool isPressed = false;
	bool isReleased = false;
	bool isMouseOnTop = false;
};

Button CreateButton(Vector2 position, float width, float height, std::string text, int fontSize, Color textColor, Color normal, Color onTop, Color pressed);
Button CreateButton(float x, float y, float width, float height, std::string text, int fontSize, Color textColor, Color normal, Color onTop, Color pressed);

Vector2 GetCenterPositionButton(Button);

void SetButtonPosition(Button& button, Vector2 newPosition);

bool MouseOnTopButton(Button&);
bool IsButtonPressed(Button&);

void SetText(Button& button, std::string text);

void DrawButton(Button);

#endif // !BUTTON
