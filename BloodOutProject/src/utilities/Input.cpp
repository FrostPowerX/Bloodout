#include "Input.h"

#include <iostream>
#include <vector>

using namespace std;

struct Key
{
	int id;

	bool isPressed;
	bool wasPressed;
};

vector<Key> keys;

enum class TYPE_KEY
{
	PRESS,
	RELEASE,
	DOWN,
	NONE
};

TYPE_KEY MouseEvent(int key, TYPE_KEY typeOfGet);
TYPE_KEY KeyEvent(int key, TYPE_KEY typeOfGet);


TYPE_KEY MouseEvent(int key, TYPE_KEY typeOfGet)
{
	TYPE_KEY type = TYPE_KEY::NONE;

	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i].id == key)
		{
			if (slGetMouseButton(key))
			{
				keys[i].isPressed = true;
			}
			else
			{
				keys[i].isPressed = false;
			}

			if (keys[i].isPressed && !keys[i].wasPressed)
			{
				keys[i].wasPressed = true;

				type = TYPE_KEY::DOWN;
			}
			else if (keys[i].isPressed && keys[i].wasPressed)
			{
				type = TYPE_KEY::PRESS;
			}
			else if (!keys[i].isPressed && keys[i].wasPressed)
			{
				type = TYPE_KEY::RELEASE;

				keys[i].wasPressed = false;
			}

			return type;
		}
	}


	Key newKey;

	newKey.id = key;
	newKey.isPressed = false;
	newKey.wasPressed = false;

	keys.push_back(newKey);


	return type;
}

TYPE_KEY KeyEvent(int key, TYPE_KEY typeOfGet)
{
	TYPE_KEY type = TYPE_KEY::NONE;

	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i].id == key)
		{
			if (slGetKey(key))
			{
				keys[i].isPressed = true;
			}
			else
			{
				keys[i].isPressed = false;
			}

			if (keys[i].isPressed && !keys[i].wasPressed)
			{
				keys[i].wasPressed = true;

				type = TYPE_KEY::DOWN;
			}
			else if (keys[i].isPressed && keys[i].wasPressed)
			{
				type = TYPE_KEY::PRESS;
			}
			else if (!keys[i].isPressed && keys[i].wasPressed)
			{
				type = TYPE_KEY::RELEASE;

				keys[i].wasPressed = false;
			}

			return type;
		}
	}

	Key newKey;

	newKey.id = key;
	newKey.isPressed = false;
	newKey.wasPressed = false;

	keys.push_back(newKey);

	return type;
}



bool GetMouseButtonPress(int key)
{
	TYPE_KEY thisType = TYPE_KEY::PRESS;

	return (MouseEvent(key, thisType) == thisType);
}

bool GetMouseButtonDown(int key)
{
	TYPE_KEY thisType = TYPE_KEY::DOWN;

	return (MouseEvent(key, thisType) == thisType);
}

bool GetMouseButtonUp(int key)
{
	TYPE_KEY thisType = TYPE_KEY::RELEASE;

	return (MouseEvent(key, thisType) == thisType);
}



bool GetKeyPress(int key)
{
	TYPE_KEY thisType = TYPE_KEY::PRESS;

	return (KeyEvent(key, thisType) == thisType);
}

bool GetKeyDown(int key)
{
	TYPE_KEY thisType = TYPE_KEY::DOWN;

	return (KeyEvent(key, thisType) == thisType);
}

bool GetKeyUp(int key)
{
	TYPE_KEY thisType = TYPE_KEY::RELEASE;

	return (KeyEvent(key, thisType) == thisType);
}
