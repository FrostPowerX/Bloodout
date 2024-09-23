#include "sl.h"

#include "Button.h"
#include "Input.h"

Button CreateButton(Vector2 position, float width, float height, std::string text, int fontSize, Color textColor, Color normal, Color onTop, Color pressed)
{
	Button newB;

	newB.rect.x = position.x;
	newB.rect.y = position.y;
	newB.rect.width = width;
	newB.rect.height = height;

	newB.text.text = text;
	newB.text.font = fontSize;
	newB.text.color = textColor;

	newB.normalColor = normal;
	newB.onMouseTopColor = onTop;
	newB.pressedColor = pressed;

	SetText(newB, text);

	return newB;
}

Button CreateButton(float x, float y, float width, float height, std::string text, int fontSize, Color textColor, Color normal, Color onTop, Color pressed)
{
	Button newB;

	newB.rect.x = x;
	newB.rect.y = y;
	newB.rect.width = width;
	newB.rect.height = height;

	newB.text.text = text;
	newB.text.font = fontSize;
	newB.text.color = textColor;

	newB.normalColor = normal;
	newB.onMouseTopColor = onTop;
	newB.pressedColor = pressed;

	SetText(newB, text);

	return newB;
}

Vector2 GetCenterPositionButton(Button button)
{
	Vector2 centerPosition;

	centerPosition.x = button.rect.x;
	centerPosition.y = button.rect.y;

	return centerPosition;
}

void SetButtonPosition(Button& button, Vector2 newPosition)
{
	button.rect.x = newPosition.x;
	button.rect.y = newPosition.y;
}

bool MouseOnTopButton(Button& button)
{
	Vector2 mousePosition;
	mousePosition.x = (float)slGetMouseX();
	mousePosition.y = (float)slGetMouseY();

	float minValueX = button.rect.x - (button.rect.width / 2);
	float minValueY = button.rect.y - (button.rect.height / 2);

	float maxValueX = button.rect.x + (button.rect.width / 2);
	float maxValueY = button.rect.y + (button.rect.height / 2);

	bool onTopX = (mousePosition.x >= minValueX && mousePosition.x <= maxValueX);
	bool onTopY = (mousePosition.y >= minValueY && mousePosition.y <= maxValueY);

	bool onTop = (onTopX && onTopY);

	button.isMouseOnTop = onTop;

	return onTop;
}

bool IsButtonPressed(Button& button)
{
	bool isReleassed = false;

	if (!MouseOnTopButton(button))
		return isReleassed;

	if (GetMouseButtonUp(SL_MOUSE_BUTTON_LEFT))
		isReleassed = (button.isMouseOnTop && button.isPressed);

	if (GetMouseButtonPress(SL_MOUSE_BUTTON_LEFT))
		button.isPressed = button.isMouseOnTop;
	else
		button.isPressed = false;

	return isReleassed;
}

void SetText(Button& button, std::string text)
{
	slSetFontSize(button.text.font);

	button.text.position.x = button.rect.x - ((float)slGetTextWidth(button.text.text.c_str()) / 2);
	button.text.position.y = button.rect.y - (button.text.font / 2);
}

void DrawButton(Button button)
{
	Color usedColor = WHITE;

	if (button.isPressed && button.isMouseOnTop)
	{
		usedColor = button.pressedColor;
	}
	else if (button.isMouseOnTop)
	{
		usedColor = button.onMouseTopColor;
	}
	else
		usedColor = button.normalColor;

	SetForeColor(usedColor);
	slRectangleFill(button.rect.x, button.rect.y, button.rect.width, button.rect.height);

	DrawText(button.text);
}