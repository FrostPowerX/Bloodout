#include "Color.h"

#include "sl.h"

void SetBackColor(Color color)
{
	slSetBackColor(color.r, color.g, color.b);
}

void SetForeColor(Color color)
{
	slSetForeColor(color.r, color.g, color.b, color.a);
}
