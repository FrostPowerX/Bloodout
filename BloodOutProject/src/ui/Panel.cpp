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

    slSetFontSize(newP.fontSizeText);

    newP.rect.width = newP.minOffSetX + newP.maxOffSetX + slGetTextWidth(newP.text.c_str());
    newP.rect.height = newP.minOffSetY + newP.maxOffSetY + newP.fontSizeText;
    
    newP.textPosition.x = newP.rect.x + newP.minOffSetX - (slGetTextWidth(newP.text.c_str()) / 2);
    newP.textPosition.y = newP.rect.y + newP.minOffSetY - (newP.fontSizeText / 2);

    return newP;
}

void SetPanelPosition(Panel& panel, Vector2 newPos)
{
    panel.rect.x = newPos.x;
    panel.rect.y = newPos.y;

    panel.rect.x = panel.rect.x;
    panel.rect.y = panel.rect.y;

    SetText(panel, panel.text);
}

void SetText(Panel& panel, string text)
{
    panel.text = text;

    slSetFontSize(panel.fontSizeText);

    panel.rect.width = panel.minOffSetX + panel.maxOffSetX + slGetTextWidth(panel.text.c_str());
    panel.rect.height = panel.minOffSetY + panel.maxOffSetY + panel.fontSizeText;

    panel.textPosition.x = panel.rect.x + panel.minOffSetX - (slGetTextWidth(panel.text.c_str()) / 2);
    panel.textPosition.y = panel.rect.y + panel.minOffSetY - panel.fontSizeText;
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
    slSetForeColor(panel.rectColor.r, panel.rectColor.g, panel.rectColor.b, panel.rectColor.a);
    slRectangleFill(panel.rect.x, panel.rect.y, panel.rect.width, panel.rect.height);

    slSetForeColor(panel.textColor.r, panel.textColor.g, panel.textColor.b, panel.textColor.a);
    slSetFontSize(panel.fontSizeText);
    slText(panel.textPosition.x, panel.textPosition.y, panel.text.c_str());
}