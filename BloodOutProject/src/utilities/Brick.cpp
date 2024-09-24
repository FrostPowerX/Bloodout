#include "Brick.h"

#include "sl.h"

Brick CreateBrick(Rectangle rect, float health, Color cT1, Color cT2, Color cT3)
{
    Brick newB;

    newB.rect = rect;

    newB.health = CreateHealth(health);

    newB.colorT1 = cT1;
    newB.colorT2 = cT2;
    newB.colorT3 = cT3;

    newB.isActive = false;

    return newB;
}

void SetPosition(Brick& b, Vector2 newPos)
{
    b.rect.x = newPos.x;
    b.rect.y = newPos.y;
}

void DrawBrick(Brick b)
{
    Color useColor = WHITE;

    if (b.health.currentHealth > 2)
        useColor = b.colorT3;
    else if (b.health.currentHealth > 1)
        useColor = b.colorT2;
    else
        useColor = b.colorT1;

    SetForeColor(useColor);
    slRectangleFill(b.rect.x, b.rect.y, b.rect.width, b.rect.height);
}
