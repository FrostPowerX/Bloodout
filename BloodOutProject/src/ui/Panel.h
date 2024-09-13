#ifndef PANEL
#define PANEL

#include <string>

#include "raylib.h"

using namespace std;

struct Panel
{
	Rectangle rect;
	
	string text;

	Vector2 textPosition;

	float minOffSetX = 0;
	float maxOffSetX = 0;

	float minOffSetY = 0;
	float maxOffSetY = 0;

	int fontSizeText = 0;

	Color rectColor = WHITE;
	Color textColor = WHITE;
};

Panel CreatePanel(Rectangle rect, string text, float minOffSetX, float maxOffSetX, float minOffSetY, float maxOffSetY, int fontSize, Color rectColor, Color textColor);

void SetPanelPosition(Panel& panel, Vector2 newPos);
/// Use this for change text
void SetText(Panel& panel, string text);
void SetColorText(Panel& panel, Color color);
void SetBackGroundColor(Panel& panel, Color color);

void DrawPanel(Panel);

#endif // !PANEL

