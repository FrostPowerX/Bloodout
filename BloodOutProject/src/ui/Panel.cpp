#include "Panel.h"

Panel CreatePanel(Rectangle rect, string text, float minOffSetX, float maxOffSetX, float minOffSetY, float maxOffSetY, int fontSize, Color rectColor, Color textColor)
{
    Panel newP;

    newP.rect = rect;
    newP.text = text;

    newP.minOffSetX = minOffSetX;
    newP.maxOffSetX = maxOffSetX;

    newP.minOffSetY = minOffSetY;
    newP.maxOffSetY = maxOffSetY;

    newP.fontSizeText = fontSize;

    newP.rectColor = rectColor;
    newP.textColor = textColor;

    newP.rect.width = newP.minOffSetX + newP.maxOffSetX + MeasureText(newP.text.c_str(), newP.fontSizeText);
    newP.rect.height = newP.minOffSetY + newP.maxOffSetY + newP.fontSizeText;
    
    newP.rect.x = newP.rect.x - (newP.rect.width / 2);
    newP.rect.y = newP.rect.y - (newP.rect.height / 2);
    
    newP.textPosition.x = newP.rect.x + newP.minOffSetX;
    newP.textPosition.y = newP.rect.y + newP.minOffSetY;

    return newP;
}

void SetPanelPosition(Panel& panel, Vector2 newPos)
{
    panel.rect.x = newPos.x;
    panel.rect.y = newPos.y;

    panel.rect.x = panel.rect.x - (panel.rect.width / 2);
    panel.rect.y = panel.rect.y - (panel.rect.height / 2);

    SetText(panel, panel.text);
}

void SetText(Panel& panel, string text)
{
    panel.text = text;

    panel.rect.width = panel.minOffSetX + panel.maxOffSetX + MeasureText(panel.text.c_str(), panel.fontSizeText);
    panel.rect.height = panel.minOffSetY + panel.maxOffSetY + panel.fontSizeText;

    panel.textPosition.x = panel.rect.x + panel.minOffSetX;
    panel.textPosition.y = panel.rect.y + panel.minOffSetY;
}

void SetColorText(Panel& panel, Color color)
{
    panel.textColor = color;
}

void SetBackGroundColor(Panel& panel, Color color)
{
    panel.rectColor = color;
}

void DrawPanel(Panel panel)
{
    DrawRectangleRec(panel.rect, panel.rectColor);

    DrawText(panel.text.c_str(), panel.textPosition.x, panel.textPosition.y, panel.fontSizeText, panel.textColor);
}