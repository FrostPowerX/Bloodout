#include "Input.h"

bool MouseKeyPress = false;

enum class TYPE_MOUSE_PRESS
{
	PRESS,
	BUP,
	BDOWN,
	NONE
};

TYPE_MOUSE_PRESS MouseEvent(int key, TYPE_MOUSE_PRESS typeOfGet);

TYPE_MOUSE_PRESS MouseEvent(int key, TYPE_MOUSE_PRESS typeOfGet)
{
	TYPE_MOUSE_PRESS type = TYPE_MOUSE_PRESS::NONE;

	if (slGetMouseButton(key))
	{
		if (!MouseKeyPress && typeOfGet == TYPE_MOUSE_PRESS::BDOWN)
		{
			type = TYPE_MOUSE_PRESS::BDOWN;
			MouseKeyPress = true;
		}
		else if (typeOfGet == TYPE_MOUSE_PRESS::PRESS)
		{
			type = TYPE_MOUSE_PRESS::PRESS;
		}
	}
	else if (MouseKeyPress && typeOfGet == TYPE_MOUSE_PRESS::BUP)
	{
		type = TYPE_MOUSE_PRESS::BUP;
		MouseKeyPress = false;
	}

	return type;
}

bool GetMouseButtonPress(int key)
{
	TYPE_MOUSE_PRESS thisType = TYPE_MOUSE_PRESS::PRESS;
	TYPE_MOUSE_PRESS type = TYPE_MOUSE_PRESS::NONE;


	if (slGetMouseButton(key))
		type = MouseEvent(key, thisType);

	return (type == thisType);
}

bool GetMouseButtonDown(int key)
{
	TYPE_MOUSE_PRESS thisType = TYPE_MOUSE_PRESS::BDOWN;
	TYPE_MOUSE_PRESS type = TYPE_MOUSE_PRESS::NONE;

	if (slGetMouseButton(key))
		type = MouseEvent(key, thisType);

	return (type == thisType);
}

bool GetMouseButtonUp(int key)
{
	TYPE_MOUSE_PRESS thisType = TYPE_MOUSE_PRESS::BUP;
	TYPE_MOUSE_PRESS type = TYPE_MOUSE_PRESS::NONE;

	if (slGetMouseButton(key))
		type = MouseEvent(key, thisType);

	return (type == thisType);
}
