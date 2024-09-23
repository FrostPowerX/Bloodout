#ifndef PANEL
#define PANEL

#include <string>

#include "Rectangle.h"
#include "Color.h"
#include "Vector2.h"
#include "Text.h"

using namespace std;

struct Panel
{
	Rectangle rect;
	
	Text text;

	float minOffSetX = 0;
	float maxOffSetX = 0;

	float minOffSetY = 0;
	float maxOffSetY = 0;

	Color rectColor = WHITE;
};

Panel CreatePanel(Rectangle rect, string text, float minOffSetX, float maxOffSetX, float minOffSetY, float maxOffSetY, int fontSize, Color rectColor, Color textColor);

void SetPanelPosition(Panel& panel, Vector2 newPos);
/// Use this for change text
void SetText(Panel& panel, string text);
void SetColorText(Panel& panel, Color color);
void SetBackGroundColor(Panel& panel, Color color);

void DrawPanel(Panel panel);

#endif // !PANEL

