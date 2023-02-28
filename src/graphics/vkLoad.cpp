/*
*   name: src/graphics/vkLoad.cpp
*   origin: Citrus Engine
*   purpose: Provide the code for engine::internals::Vulkan::vkLoad()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifdef __unix__

#include <unistd.h>
#include <dlfcn.h>

#elif defined(_WIN32)

#include <Windows.h>

#endif

#include <stdlib.h>
#include <vulkan.h>
#include "core/crash.hpp"
#include "core/log.hpp"
#include "core/mem.hpp"
#include "core/extensions.h"
#include "core/vector.hpp"
#include "graphics/initGL.hpp"
#include "graphics/vkGlobals.hpp"
#include "graphics/vkInit.hpp"

using namespace engine;
using namespace internals;

dllptr_t Vulkan::libvulkan;

Vulkan::vkGIPA_t Vulkan::vkGetInstanceProcAddr;
Vulkan::vkGDPA_t Vulkan::vkGetDeviceProcAddr;
VkAllocationCallbacks Vulkan::vkAllocCallbacks;

VkInstance Vulkan::instance;
VkDevice Vulkan::device;

VkPhysicalDevice Vulkan::physicalDevice;
VkPhysicalDeviceProperties Vulkan::physicalDeviceProperties;
VkPhysicalDeviceMemoryProperties Vulkan::physicalDeviceMemoryProperties;
size_t Vulkan::physicalDeviceVRAM;

static inline bool deviceEligable(VkPhysicalDevice dev, VkPhysicalDeviceProperties *devP, Vector<VkQueueFamilyProperties> &queueP, VkPhysicalDeviceMemoryProperties &deviceMemoryProperties, size_t &vram)
{
	// Get the device properties
	vkCall(vkGetPhysicalDeviceProperties, dev, &devP);

	// Don't use a CPU
	if(devP->deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
		return false;

	// Get device queue properties

	int qCount;
	VkQueueFamilyProperties *qProperties;
	vkCall(vkGetPhysicalDeviceQueueFamilyProperties, dev, &qCount, NULL);
	qProperties = memalloc(sizeof(VkQueueFamilyProperties) * qCount, MEM_FLAG_UNIT_BYTE);
	vkCall(vkGetPhysicalDeviceQueueFamilyProperties, dev, &qCount, qProperties);
	for(int i = 0; i < qCount; i++)
	{
		queueP.push(qProperties[i]);
	}
	memfree(qProperties);

	// Perform queue filtering

	int gSupportCount = 0;
	int cSupportCount = 0;
	int tSupportCount = 0;
	for(int i = 0; i < qCount; i++;)
	{
		if(queueP[i].queueFlags & VkQueueFlagBits.VK_QUEUE_GRAPHICS_BIT) gSupportCount++;
		if(queueP[i].queueFlags & VkQueueFlagBits.VK_QUEUE_COMPUTE_BIT) cSupportCount++;
		if(queueP[i].queueFlags & VkQueueFlagBits.VK_QUEUE_TRANSFER_BIT) tSupportCount++;
	}

	if(gSupportCount < 1 || cSupportCount < 1 || tSupportCount < 1) return false;

	// Perform memory filtering

	vram = 0;
	vkCall(vkGetPhysicalDeviceMemoryProperties, dev, &deviceMemoryProperties);
	for(int i = 0; i < deviceMemoryProperties.memoryHeapCount; i++)
		vram += deviceMemoryProperties.memoryHeaps[i].size;
	
	// 3/4 GB as an arbitrary limit
	if(vram < 1024 * 1024 * 768) return false;
	
	return true;
}

// Calculate a score for the device
static inline int calcDeviceScore(VkPhysicalDeviceProperties devP, Vector<VkQueueFamilyProperties> queueP, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, size_t vram)
{
	int score = 0;
	score += vram/(1024 * 1024);
	score += (devP.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ) 1 : 0;
	
	// Could be useful later
	score += VK_API_VERSION_MAJOR(devP.apiVersion)
	
	// TODO: Add code that takes devP.limits into account
	// TODO: Add code that takes queueP into account... somehow

	return score;
}

static inline void countInferiors(Vector<int> &inferiors, Vector<int> deviceScore)
{
	for(int i = 0; i < deviceScore.getCount(); i++)
	{
		int count = 0;
		for(int j = 0; j < deviceScore.getCount(); j++)
		{
			if(j != i)
			{
				count = (deviceScore[i] => deviceScore[j]) ? count + 1 : count;
				count = (deviceScore[i] == deviceScore[j] && j < i) ? count - 1 : count;
			}
		}
		deviceInferiorCount.push(count);
	}
}

int Vulkan::vkLoad()
{
	// TODO: If both Vulkan and OpenGL are being compiled, make them both DLLs
    // TODO: If just OpenGL is being compiled, embed it into the main archive
	#ifdef __unix__

	Vulkan::libvulkan = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_GLOBAL);
	if(Vulkan::libvulkan == NULL)
	{
		#if !defined(_OPENGL_)
		
		log(STRINGIFY(engine::internals::Vulkan::vkLoad()), "libvulkan.so.1 not found!");
		exit(VULKAN_NOT_FOUND);
		
		#else
		
		log(STRINGIFY(engine::internals::Vulkan::vkLoad()/main()), "libvulkan.so.1 not found, loading OpenGL instead");
		// TODO: engine::errorcode
		return OpenGL::loadGL();
		
		#endif
	}

	// Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
	Vulkan::vkGetInstanceProcAddr = (Vulkan::vkGIPA_t)dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetInstanceProcAddr));
	Vulkan::vkGetDeviceProcAddr = (Vulkan::vkGIDA_t)dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetDeviceProcAddr));

	#elif defined(_WIN32)

	Vulkan::libvulkan = LoadLibraryA("Vulkan-1.dll");
	if(Vulkan::libvulkan == NULL)
	{
		#ifndef _OPENGL_
		
		log(STRINGIFY(engine::internals::Vulkan::vkLoad()), "Vulkan-1.dll not found!");
		exit(VULKAN_NOT_FOUND);
		
		#else
		
		log(STRINGIFY(engine::internals::Vulkan::vkLoad()/main()), "Vulkan-1.dll not found, loading OpenGL instead");
		// TODO: engine::errorcode
		return OpenGL::loadGL();
		
		#endif
	}

    // Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
	Vulkan::vkGetInstanceProcAddr = (Vulkan::vkGIPA_t)GetProcAddress(Vulkan::libvulkan, _STRINGIFY_(vkGetInstanceProcAddr));
	Vulkan::vkGetDeviceProcAddr = (Vulkan::vkGDPA_t)GetProcAddress(Vulkan::libvulkan, _STRINGIFY_(vkGetDeviceProcAddr));

	#endif

	if(vkGetInstanceProcAddr == NULL || vkGetDeviceProcAddr == NULL)
	{
		#ifndef _OPENGL_
		
		log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "Failure to load critical Vulkan functions!");
		exit(VK_LOAD_FAILURE);
		
		#else
		
		log(STRINGIFY(engine::internals::Vulkan::vkLoad()/main()), "Failure to load critical Vulkan functions, loading OpenGL instead");
		// TODO: engine::errorcode
		return OpenGL::loadGL();
		
		#endif
	}

	// Initalize Vulkan

	// Vulkan application info

	VkApplicationInfo aInfo;
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	// _APPLICATION_NAME_ defined during compilation
	info.pApplicationName = _APPLICATION_NAME_;
	info.applicationVersion = _GAME_VERSION_INT_;
	info.pNext = NULL;
	info.pEngineName = "Citrus Engine Builtin Vulkan Render Engine";
	// _CITRUS_ENGINE_VERSION_ defined during compilation
	info.engineVersion = _CITRUS_ENGINE_VERSION_;
	info.apiVersion = VK_VERSION_1_0;

	// Vulkan instance creation info

	VkInstanceCreateInfo iInfo;
	iInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	iInfo.pApplicationInfo = &aInfo;
	// TODO: Add the layer information.
	iInfo.enabledExtensionCount = 0;
	iInfo.ppEnabledExtensionNames = NULL;

	// Initalize the instance
	if(vkInstanceCall(vkCreateInstance, 0, &iInfo, NULL, &Vulkan::instance) != VK_SUCCESS)
	{
		#ifndef _OPENGL_
		
		log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "Failure to create Vulkan instance!");
		exit(VK_LOAD_FAILURE);
		
		#else
		
		log(_STRINGIFY_(main()/engine::internals::Vulkan::vkLoad()), "Failure to create Vulkan instance, loading OpenGL instead.");
		// TODO: engine::errorcode
		return OpenGL::initGL();
		
		#endif
	}

	// TODO: Validation layers

	// Select the physical device

	// Get the count

	int devCount = 0;
	vkInstanceCall(vkEnumeratePhysicalDevices, Vulkan::instance, &devCount, NULL);
	if(devCount == 0) 
	{
		#ifndef _OPENGL_
		
		log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "No (Vulkan supporting) GPUs found!");
		exit(COMPATIBLE_GPU_NOT_FOUND);
		
		#else
		
		log(_STRINGIFY_(main()/engine::internals::Vulkan::vkLoad()), "No (Vulkan supporting) GPUs found, loading OpenGL instead.");
		// TODO: engine::errorcode
		return OpenGL::initGL();
		
		#endif
	}

	// Get the handles

	VkPhysicalDevice *devices = memalloc(sizeof(VkPhysicalDevice) * devCount, 0);
	vkInstanceCall(vkEnumeratePhysicalDevices, Vulkan::instance, &devCount, devices);

	// Filter out all of the eligible devices

	Vector<VkPhysicalDevice> eligibleDevices;
	Vector<VkPhysicalDeviceProperties> deviceProperties;
	Vector<Vector<VkQueueFamilyProperties>> deviceQueueProperties;
	Vector<VkPhysicalDeviceMemoryProperties> deviceMemoryProperties;
	Vector<size_t> deviceVram;
	Vector<int> deviceScore;
	for(int i = 0; i < devCount; i++)
	{
		VkPhysicalDeviceProperties p;
		Vector<VkQueueFamilyProperties> qp;
		VkPhysicalDeviceMemoryProperties mp;
		size_t tmpvram;
		if(deviceEligable(devices[i], &p, qp, mp, tmpvram))
		{
			eligibleDevices.push(devices[i]);
			deviceProperties.push(p);
			deviceQueueProperties.push(qp);
			deviceMemoryProperties.push(mp);
			deviceVram.push(tmpvram);
			deviceScore.push(calcDeviceScore(p, qp, mp, tmpvram));
		}
	}
	memfree(devices);

	if(!eligibleDevices.getCount())
	{
		engineLog.log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "No eligible GPUs found");
		exit(COMPATIBLE_GPU_NOT_FOUND);
	}

	// Evaluate the devices

	// TODO: Optimize this code
	while(eligibleDevices.getCount() != 1)
	{
		// Vector for counting each device and what it has a higher score than
		Vector<int> deviceInferiorCount;
		countInferiors(deviceInferiorCount, deviceScore);

		// Set to true everytime something isn't removed
		bool repeat = true;

		for(int i = 0; i < deviceInferiorCount.getCount(); i++)
		{
			// Filter out everything that isn't better than something
			if(deviceInferiorCount[i] == 0)
			{
				eligibleDevices.rm(i);
				deviceProperties.rm(i);
				deviceQueueProperties.rm(i);
				deviceMemoryProperties.rm(i);
				deviceVram.rm(i);
				deviceScore.rm(i);
				deviceInferiorCount.rm(i);
				repeat = false;
			}
		}

		// Break tie by selecting first dedicated (non integrated) GPU found, if none are found, fall back on first GPU found.
		if(repeat)
		{
			VkPhysicalDevice dev = eligibleDevices[0];

			for(int i = 0; i < deviceProperties.getCount(); i++)
			{
				if(deviceProperties[i].deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || deviceProperties[i].deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
				{
					dev = eligibleDevices[i];
					break;
				}
			}

			for(int i = 0; i < eligibleDevices.getCount(); i++)
			{
				if(eligibleDevices[i] != dev)
				{
					eligibleDevices.rm(i);
					deviceProperties.rm(i);
					deviceQueueProperties.rm(i);
					deviceMemoryProperties.rm(i);
					deviceVram.rm(i);
					deviceScore.rm(i);
				}
			}
		}
	}

	// Load the globals for the physical device

	Vulkan::physicalDevice = eligibleDevices[0];
	Vulkan::physicalDeviceProperties = deviceProperties[0];
	Vulkan::physicalDeviceMemoryProperties = deviceMemoryProperties[0];
	Vulkan::physicalDeviceVRAM = deviceVram[0];

	// Log the choice

	log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "Selected GPU: %s", deviceProperties[0].deviceName);

	// TODO: Add code to update the version and select the Vulkan function

	// Create the logical device
	
	VkDeviceCreateInfo devInfo;
	VkDeviceQueueCreateInfo queueMkInfo;
	VkPhysicalDeviceFeatures devFeatures;
	devInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	devInfo.pNext = NULL;
	devInfo.flags = 0;

	// TODO: create the queues
	// TODO: handle extensions and layers
	// TODO: select device features

	if(vkCall(vkCreateDevice, Vulkan::physicalDevice, &devInfo, &device) != VK_SUCCESS)
	{
		log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "Failure to create the logical device");
		exit(VK_LOAD_FAILURE);
	}

}
