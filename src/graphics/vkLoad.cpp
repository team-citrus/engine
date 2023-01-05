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
#include "include/core/crash.hpp"
#include "include/core/log.hpp"
#include "include/core/mem.hpp"
#include "include/core/extensions.hpp"
#include "include/core/vector.hpp"
#include "include/graphics/vkGlobals.hpp"
#include "include/graphics/vkInit.hpp"

using namespace engine;
using namespace internals;

dllptr_t Vulkan::libvulkan;

Vulkan::vkGIPA_t Vulkan::vkGetInstanceProcAddr;
Vulkan::vkGDPA_t Vulkan::vkGetDeviceProcAddr;
VkAllocationCallbacks Vulkan::vkAllocCallbacks;

VkInstance Vulkan::instance;
VkDevice Vulkan::device;

static inline bool deviceEligable(VkPhysicalDevice dev, VkPhysicalDeviceProperties *devP, Vector<VkQueueFamilyProperties> &queueP)
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
}

int Vulkan::vkLoad()
{
	#ifdef __unix__

	Vulkan::libvulkan = dlopen("libvulkan.so.1", RTLD_NOW);
	if(Vulkan::libvulkan == NULL)
	{
		engineLog.log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "libvulkan.so.1 not found");
		exit(VULKAN_NOT_FOUND);
	}

	// Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
	Vulkan::vkGetInstanceProcAddr = (Vulkan::vkGIPA_t)dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetInstanceProcAddr));
	Vulkan::vkGetDeviceProcAddr = (Vulkan::vkGIDA_t)dlsym(Vulkan::libvulkan, _STRINGIFY_(vkGetDeviceProcAddr));

	#elif defined(_WIN32)

	Vulkan::libvulkan = LoadLibraryA("Vulkan-1.dll");
	if(Vulkan::libvulkan == NULL)
	{
		engineLog.log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "Vulkan-1.dll not found");
		exit(VULKAN_NOT_FOUND);
	}

    // Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
    Vulkan::vkGetInstanceProcAddr = (Vulkan::vkGIPA_t)GetProcAddress(Vulkan::libvulkan, _STRINGIFY_(vkGetInstanceProcAddr));
	Vulkan::vkGetDeviceProcAddr = (Vulkan::vkGDPA_t)GetProcAddress(Vulkan::libvulkan, _STRINGIFY_(vkGetDeviceProcAddr));

	#endif

	if(vkGetInstanceProcAddr == NULL || vkGetDeviceProcAddr == NULL)
	{
		engineLog.log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "Failure to load critical Vulkan functions");
		exit(VK_LOAD_FAILURE);
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
	info.apiVersion = VULKAN_VERSION;

	// Vulkan instance creation info

	VkInstanceCreateInfo iInfo;
	iInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	iInfo.pApplicationInfo = &aInfo;
	// TODO: Add the layer information.
	iInfo.enabledExtensionCount = 0;
	iInfo.ppEnabledExtensionNames = NULL;

	// Initalize the instance
	vkInstanceCall(vkCreateInstance, 0, &iInfo, NULL, &Vulkan::instance);

	// TODO: Validation layers

	// Select the physical device

	// Get the count

	int devCount;
	vkInstanceCall(vkEnumeratePhysicalDevices, Vulkan::instance, &devCount, NULL);
	if(devCount == 0) 
	{
		engineLog.log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "No compatible GPUs found");
		exit(COMPATIBLE_GPU_NOT_FOUND);
	}

	// Get the handles

	VkPhysicalDevice *devices = memalloc(sizeof(VkPhysicalDevice) * devCount, 0);
	vkInstanceCall(vkEnumeratePhysicalDevices, Vulkan::instance, &devCount, devices);

	// Filter out all of the eligible devices

	Vector<VkPhysicalDevice> eligibleDevices;
	Vector<VkPhysicalDeviceProperties> deviceProperties;
	Vector<Vector<VkQueueFamilyProperties>> deviceQueueProperties;
	for(int i = 0; i < devCount; i++)
	{
		VkPhysicalDeviceProperties p;
		Vector<VkQueueFamilyProperties> qp;
		if(deviceEligable(devices[i], &p, qp))
		{
			eligibleDevices.push(devices[i]);
			deviceProperties.push(p);
		}
	}
	memfree(devices);

	if(!eligibleDevices.getCount())
	{
		engineLog.log(_STRINGIFY_(engine::internals::Vulkan::vkLoad()), "No eligible GPUs found");
		exit(COMPATIBLE_GPU_NOT_FOUND);
	}


}