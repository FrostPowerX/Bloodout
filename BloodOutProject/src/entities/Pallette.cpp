#include "Pallette.h"
#include "..\utilities\Constants.h"

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

void MovePallette(Pallette& pallette, float dirX)
{
    if (dirX > 1)
        dirX = 1;
    else if (dirX < -1)
        dirX = -1;

    pallette.rect.y += dirX * pallette.speed * GetFrameTime();
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
    Vector3 pos;
    pos.x = pallette.rect.x + (pallette.rect.width / 2) - (screenWidth / 2);
    pos.y = 10;
    pos.z = pallette.rect.y + (pallette.rect.height / 2) - (screenHeight / 2);

    DrawCube(pos, pallette.rect.width, 15, pallette.rect.height, pallette.color);
    DrawCubeWires(pos, pallette.rect.width, 15, pallette.rect.height, pallette.borderColor);
    //DrawRectangleRec(pallette.rect, pallette.color);
}
