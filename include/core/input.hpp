/*
*   name: include/core/input.hpp
*   origin: Citrus Engine
*   purpose: The header for the input system
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_INPUT_SYSTEM_HPP__
#define CITRUS_ENGINE_INPUT_SYSTEM_HPP__

namespace engine
{
	#ifdef _WIN32
	namespace internals
	{
		extern uint8_t currentInput[256];
		extern uint8_t prevInput[256];
	}
	#endif
	// TODO: Defines for each key value, different for windows and linux

	// Returns true while a key is down
	bool getKey(char key);
	// Returns true the first frame a key is down
	bool getKeyDown(char key);
	// Returns true when a key is released
	bool getKeyUp(char key);

	// Returns true while a key is down
	bool getMouseButton(int num);
	// Returns true the first frame a key is down
	bool getMouseButtonDown(int num);
	// Returns true when a key is released
	bool getMouseButtonUp(int num);

	// Returns true if any key is down
	bool anyKey();

	// TODO: Add controller functions

	// TODO: Rust interop
};

#endif