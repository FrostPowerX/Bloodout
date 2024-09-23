#include "Text.h"
#include "sl.h"

Text CreateText(std::string text, int x, int y, int font, Color color)
{
    Text newText;

    newText.text = text;

    newText.position.x = (float)x;
    newText.position.y = (float)y;

    newText.font = font;

    newText.color = color;

    return newText;
}

void DrawText(Text text)
{
    slSetForeColor(text.color.r, text.color.g, text.color.b, text.color.a);
    slSetFontSize(text.font);
    slText(text.position.x, text.position.y, text.text.c_str());
}
