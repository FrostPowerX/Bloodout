#ifndef BUTTON
#define BUTTON

#include <string>

#include "Rectangle.h"
#include "Vector2.h"
#include "Color.h"
#include "Text.h"

struct Button
{
	Rectangle rect;

	Text text;

	Color normalColor = WHITE;
	Color onMouseTopColor = WHITE;
	Color pressedColor = WHITE;

	bool isPressed = false;
	bool isReleased = false;
	bool isMouseOnTop = false;
};

Button CreateButton(Vector2 position, float width, float height, std::string text, int fontSize, Color textColor, Color normal, Color onTop, Color pressed);
Button CreateButton(float x, float y, float width, float height, std::string text, int fontSize, Color textColor, Color normal, Color onTop, Color pressed);

Vector2 GetCenterPositionButton(Button button);

void SetButtonPosition(Button& button, Vector2 newPosition);

bool MouseOnTopButton(Button& button);
bool IsButtonPressed(Button& button);

void SetText(Button& button, std::string text);

void DrawButton(Button button);

#endif // !BUTTON
