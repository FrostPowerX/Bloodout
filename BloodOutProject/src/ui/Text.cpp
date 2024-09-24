#include "Text.h"
#include "sl.h"

Text CreateText(std::string text, int x, int y, int fontSize, Color color)
{
    Text newText;

    newText.text = text;

    newText.position.x = (float)x;
    newText.position.y = (float)y;

    newText.fontSize = fontSize;

    newText.color = color;

    return newText;
}

void DrawText(Text text)
{
    SetForeColor(text.color);
    slSetFontSize(text.fontSize);
    slText(text.position.x, text.position.y, text.text.c_str());
}
