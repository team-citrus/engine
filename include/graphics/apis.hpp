#ifndef CITRUS_ENGINE_GRAPHICS_APIS_HPP__
#define CITRUS_ENGINE_GRAPHICS_APIS_HPP__

/* Engine stuff */
namespace engine
{
	// Graphics API codes, for use in the variable gAPI.
	enum graphicsAPICodes
	{   
		// Use Vulkan under the hood
		vulkan = 1 << 1,
		// Use OpenGL under the hood
		openGL = 1 << 0,
		// Reserved, might use this for DirectX later
		reserved = 1 << 2
	};

	/* Graphics API for the engine to use for under the hood rendering. */
	int gAPI;

	/*	Get supported graphics APIs.
	*	@return Returns a bitfield telling which APIs are supported.
	*	Bit 0 is if OpenGL is supported,
	*	bit 1 is if Vulkan is supported,
	*	bit 2 is if DirectX is supported,
	*	the rest are undefined.
	*/
	int supportedGAPIs();
};

#endif