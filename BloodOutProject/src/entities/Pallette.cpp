#include "Pallette.h"

#include "sl.h"
#include "Constants.h"

Pallette CreatePallette(Vector2 position, Color color, float width, float height, float speed)
{
    Pallette newPallette;

    newPallette.rect.x = position.x;
    newPallette.rect.y = position.y;
    newPallette.color = color;

    newPallette.rect.width = width;
    newPallette.rect.height = height;
    
    newPallette.direction = 0;
    newPallette.speed = speed;

    return newPallette;
}

void MovePallette(Pallette& pallette, float dirX, float dirY)
{
    if (dirX > 1)
        dirX = 1;
    else if (dirX < -1)
        dirX = -1;

    if (dirY > 1)
        dirY = 1;
    else if (dirY < -1)
        dirY = -1;

    pallette.rect.x += dirX * pallette.speed * slGetDeltaTime();

    pallette.rect.y += dirY * pallette.speed * slGetDeltaTime();
}

void ChangeColorPallette(Pallette& rect, Color newColor)
{
    rect.color = newColor;
}

void ChangeWidthPall(Pallette& rect, float newWidth)
{
    rect.rect.width = newWidth;
}

void ChangeHeightPall(Pallette& rect, float newHeight)
{
    rect.rect.height = newHeight;
}

void ChangeSpeedPallette(Pallette& pallette, float speed)
{
    pallette.speed = speed;
}

void DrawPallette(Pallette& pallette)
{
    slSetForeColor(pallette.color.r, pallette.color.g, pallette.color.b, pallette.color.a);
    slRectangleFill(pallette.rect.x, pallette.rect.y, pallette.rect.width, pallette.rect.height);
}
