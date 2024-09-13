#include "Text.h"

Text CreateText(std::string text, int x, int y, int font, Color color)
{
    Text newText;

    newText.text = text;

    newText.position.x = x;
    newText.position.y = y;

    newText.font = font;

    newText.color = color;

    return newText;
}

void DrawText(Text text)
{
    DrawText(text.text.c_str(),text.position.x, text.position.y, text.font, text.color);
}
