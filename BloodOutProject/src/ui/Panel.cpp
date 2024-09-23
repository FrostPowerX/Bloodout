#include "Panel.h"
#include "sl.h"

Panel CreatePanel(Rectangle rect, string text, float minOffSetX, float maxOffSetX, float minOffSetY, float maxOffSetY, int fontSize, Color rectColor, Color textColor)
{
    Panel newP;

    newP.rect = rect;
    newP.text.text = text;

    newP.minOffSetX = minOffSetX;
    newP.maxOffSetX = maxOffSetX;

    newP.minOffSetY = minOffSetY;
    newP.maxOffSetY = maxOffSetY;

    newP.text.font = fontSize;

    newP.rectColor = rectColor;
    newP.text.color = textColor;

    slSetFontSize(newP.text.font);

    newP.rect.width = newP.minOffSetX + newP.maxOffSetX + slGetTextWidth(newP.text.text.c_str());
    newP.rect.height = newP.minOffSetY + newP.maxOffSetY + newP.text.font;
    
    newP.text.position.x = newP.rect.x + newP.minOffSetX - (slGetTextWidth(newP.text.text.c_str()) / 2);
    newP.text.position.y = newP.rect.y + newP.minOffSetY - (newP.text.font / 2);

    return newP;
}

void SetPanelPosition(Panel& panel, Vector2 newPos)
{
    panel.rect.x = newPos.x;
    panel.rect.y = newPos.y;

    panel.rect.x = panel.rect.x;
    panel.rect.y = panel.rect.y;

    SetText(panel, panel.text.text);
}

void SetText(Panel& panel, string text)
{
    panel.text.text = text;

    slSetFontSize(panel.text.font);

    panel.rect.width = panel.minOffSetX + panel.maxOffSetX + slGetTextWidth(panel.text.text.c_str());
    panel.rect.height = panel.minOffSetY + panel.maxOffSetY + panel.text.font;

    panel.text.position.x = panel.rect.x + panel.minOffSetX - (slGetTextWidth(panel.text.text.c_str()) / 2);
    panel.text.position.y = panel.rect.y + panel.minOffSetY - panel.text.font;
}

void SetColorText(Panel& panel, Color color)
{
    panel.text.color = color;
}

void SetBackGroundColor(Panel& panel, Color color)
{
    panel.rectColor = color;
}

void DrawPanel(Panel panel)
{
    SetForeColor(panel.rectColor);
    slRectangleFill(panel.rect.x, panel.rect.y, panel.rect.width, panel.rect.height);

    DrawText(panel.text);
}