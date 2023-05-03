/*
*   name: src/core/input.cpp
*   origin: Citrus Engine
*   purpose: The code for the input system
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#include "input.hpp"

// Welcome to portability hell, population, us
#ifdef _WIN32

#include <Windows.h>

uint8_t engine::internals::currentInput[256];
uint8_t engine::internals::prevInput[256]; // Used for getKeyDown and getMouseButtonDown

// Returns true while a key is down
bool engine::getKey(char key)
{
	return (engine::internals::currentInput[key] >> 7) == 1;
}

// Returns true the first frame a key is down
bool engine::getKeyDown(char key)
{
	return ((engine::internals::currentInput[key] >> 7) == 1) && ((engine::internals::prevInput[key] >> 7) == 0);
}

// Returns true when a key is released
bool engine::getKeyUp(char key)
{
	return ((engine::internals::currentInput[key] >> 7) == 0) && ((engine::internals::prevInput[key] >> 7) == 1);
}

// Returns true while a key is down
bool engine::getMouseButton(int num)
{
	switch (num)
	{
		case 1:
		return engine::getKey(VK_LBUTTON);
		case 2:
		return engine::getKey(VK_MBUTTON);
		case 3:
		return engine::getKey(VK_RBUTTON);
		default:
		return false;
	}
}
// Returns true the first frame a key is down
bool engine::getMouseButtonDown(int num)
{
	switch (num)
	{
		case 1:
		return engine::getKeyDown(VK_LBUTTON);
		case 2:
		return engine::getKeyDown(VK_MBUTTON);
		case 3:
		return engine::getKeyDown(VK_RBUTTON);
		default:
		return false;
	}
}
// Returns true when a key is released
bool getMouseButtonUp(int num)
{
	switch (num)
	{
		case 1:
		return engine::getKeyUp(VK_LBUTTON);
		case 2:
		return engine::getKeyUp(VK_MBUTTON);
		case 3:
		return engine::getKeyUp(VK_RBUTTON);
		default:
		return false;
	}
}

#else



#endif