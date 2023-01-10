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
	// Underlying class of the input system
	class INPUT_SYSTEM
	{
		public:
		// TODO: Unicode-ify this

		// Returns true while a key is down
		bool getKey(char key);
		// Returns true the first frame a key is down
		bool getKeyDown(char key);
		// Returns true when a key is released
		bool getKeyUp(char key);

		// Returns true while a mouse button is down
		bool getMouseButton(int button);
		// Returns true the first frame a mouse button is down
		bool getMouseButtonDown(int button);
		// Returns true when a mouse button is released
		bool getMouseButtonUp(int button);

		// Returns true if any key is down
		bool anyKey();
		
		// TODO: Add controller functions
	};

	INPUT_SYSTEM input;
};

#endif