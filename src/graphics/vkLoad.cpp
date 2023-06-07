/*
*   name: src/graphics/vkLoad.cpp
*   origin: Citrus Engine
*   purpose: Provide the code for engine::internals::vkLoad()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include "core/os.h"

#ifdef CITRUS_ENGINE_UNIX

#include <unistd.h>
#include <dlfcn.h>
#include "core/XLibglobals.h"

#else

#include <Windows.h>
#include "core/windowsGlobals.h"

#endif

#define VK_NO_PROTOTYPES
#include <stdlib.h>
#include <vulkan.h>
#include "core/log.hpp"
#include "core/mem.h"
#include "core/extensions.h"
#include "core/vector.hpp"
#include "graphics/vkGlobals.h"
#include "graphics/vkInit.h"
#include "graphics/vkCall.h"

dllptr_t libvulkan;

vkGIPA_t vkGetInstanceProcAddrPtr;
vkGDPA_t vkGetDeviceProcAddrPtr;

VkInstance instance;
VkDevice device;

VkPhysicalDevice physicalDevice;
VkPhysicalDeviceProperties physicalDeviceProperties;
VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
size_t physicalDeviceVRAM;

VkSwapchainKHR swapchain = VK_NULL_HANDLE;
VkSufaceKHR surface;

// TODO: Convert to pure C, maybe

static inline bool deviceEligable(VkPhysicalDevice dev, VkPhysicalDeviceProperties *devP, Vector<VkQueueFamilyProperties> &queueP, VkPhysicalDeviceMemoryProperties &deviceMemoryProperties, size_t &vram)
{
	// Get the device properties
	vkNullCall(STRINGIFY(vkGetPhysicalDeviceProperties), dev, &devP);

	// Don't use a CPU
	if(devP->deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
		return false;

	// Get device queue properties

	int qCount;
	VkQueueFamilyProperties *qProperties;
	vkNullCall(STRINGIFY(vkGetPhysicalDeviceQueueFamilyProperties), dev, &qCount, NULL);
	qProperties = (VkQueueFamilyProperties*)memalloc(sizeof(VkQueueFamilyProperties) * qCount);
	vkNullCall(STRINGIFY(vkGetPhysicalDeviceQueueFamilyProperties), dev, &qCount, qProperties);

	for(int i = 0; i < qCount; i++) {
		queueP.push(qProperties[i]);
	}

	memfree(qProperties);

	// Perform queue filtering

	int gSupportCount = 0;
	int cSupportCount = 0;
	int tSupportCount = 0;
	for(int i = 0; i < qCount; i++) {
		if(queueP[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) gSupportCount++;
		if(queueP[i].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) cSupportCount++;
		if(queueP[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) tSupportCount++;
	}

	if(gSupportCount < 1 || cSupportCount < 1 || tSupportCount < 1) return false;

	// Perform memory filtering

	vram = 0;
	vkNullCall(STRINGIFY(vkGetPhysicalDeviceMemoryProperties), dev, &deviceMemoryProperties);
	for(int i = 0; i < deviceMemoryProperties.memoryHeapCount; i++)
		vram += deviceMemoryProperties.memoryHeaps[i].size;
	
	// 1/2 GB as an arbitrary limit in case no other is set
	
	if(vram < 
		#ifdef _MINIMUM_VRAM_
		_MINIMUM_VRAM_
		#else
		(1024 * 1024 * 512)
		#endif
	) return false;
	
	return true;
}

// Calculate a score for the device
static inline int calcDeviceScore(VkPhysicalDeviceProperties devP, Vector<VkQueueFamilyProperties> queueP, VkPhysicalDeviceMemoryProperties deviceMemoryProperties, size_t vram)
{
	int score = 0;
	score += vram/(1024 * 1024);
	score += (devP.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ) ? 1 : 0;
	
	// Could be useful later
	score += VK_API_VERSION_MAJOR(devP.apiVersion);
	
	// TODO: Add code that takes devP.limits into account
	// TODO: Add code that takes queueP into account... somehow

	return score;
}

static inline void countInferiors(Vector<int> &inferiors, Vector<int> deviceScore)
{
	for(int i = 0; i < deviceScore.getCount(); i++) {
		int count = 0;
		for(int j = 0; j < deviceScore.getCount(); j++) {
			if(j != i) {
				count = (deviceScore[i] >= deviceScore[j]) ? count + 1 : count;
				count = (deviceScore[i] == deviceScore[j] && j < i) ? count - 1 : count;
			}
		}

		inferiors.push(count);
	}
}

NOMANGLE void graphics_init()
{
	#ifdef CITRUS_ENGINE_WINDOWS

	winit();
	vkLoad();
	ShowWindow(hwnd, showStyle);

	#else

	xinit();
	vkLoad();
	XMapWindow(display, window);

	#endif
}

NOMANGLE int vkLoad()
{
	#ifdef CITRUS_ENGINE_UNIX

	libvulkan = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_GLOBAL);
	if(libvulkan == NULL) {
		log(STRINGIFY(engine::internals::vkLoad()), "libvulkan.so.1 not found!");
		exit(-1);
	}

	// Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
	vkGetInstanceProcAddrPtr = (vkGIPA_t)dlsym(libvulkan, STRINGIFY(vkGetInstanceProcAddr));
	vkGetDeviceProcAddrPtr = (vkGIDA_t)dlsym(libvulkan, STRINGIFY(vkGetDeviceProcAddr));

	#else

	libvulkan = LoadLibraryA("Vulkan-1.dll");
	if(libvulkan == NULL) {
		log(STRINGIFY(engine::internals::vkLoad()), "Vulkan-1.dll not found!");
		exit(-1);
	}

	// Get good ol' vkGetInstanceProcAddr and vkGetDeviceProcAddr
	vkGetInstanceProcAddrPtr = (vkGIPA_t)GetProcAddress(libvulkan, STRINGIFY(vkGetInstanceProcAddr));
	vkGetDeviceProcAddrPtr = (vkGDPA_t)GetProcAddress(libvulkan, STRINGIFY(vkGetDeviceProcAddr));

	#endif

	if(vkGetInstanceProcAddrPtr == NULL || vkGetDeviceProcAddrPtr == NULL) {
		log(STRINGIFY(engine::internals::vkLoad()), "Failure to load critical Vulkan functions!");
		exit(-1);
	}

	// Initalize Vulkan

	// Vulkan application info

	VkApplicationInfo aInfo;
	aInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	// TODO: info.pApplicationName = ;
	// TODO: info.applicationVersion = ;
	aInfo.pNext = NULL;
	aInfo.pEngineName = "Citrus Engine Builtin Vulkan Render Engine";
	aInfo.engineVersion = (0xec << 24) | (1 << 8); // This variant of the Citrus Engine always has a variant number of 0xec
	aInfo.apiVersion = VK_VERSION_1_0;

	// Vulkan instance creation info

	VkInstanceCreateInfo iInfo;
	iInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	iInfo.pApplicationInfo = &aInfo;
	// TODO: Add the layer information.
	iInfo.enabledExtensionCount = 2;
	iInfo.ppEnabledExtensionNames = ["VK_KHR_swapchain", "VK_KHR_surface"];

	// Initalize the instance
	if(vkNullCall(STRINGIFY(vkCreateInstance), 0, &iInfo, NULL, &instance) != VK_SUCCESS) {
		log(STRINGIFY(engine::internals::vkLoad()), "Failure to create Vulkan instance!");
		exit(-1);
	}

	// TODO: Validation layers

	// Select the physical device

	// Get the count

	int devCount = 0;
	vkInstanceCall(STRINGIFY(vkEnumeratePhysicalDevices), instance, instance, &devCount, NULL);
	if(devCount == 0) {
		log(STRINGIFY(engine::internals::vkLoad()), "No (Vulkan supporting) GPUs found!");
		exit(-1);
	}

	// Get the handles

	VkPhysicalDevice *devices = (VkPhysicalDevice*)memalloc(sizeof(VkPhysicalDevice) * devCount);
	vkInstanceCall(STRINGIFY(vkEnumeratePhysicalDevices), instance, instance, &devCount, devices);

	// Filter out all of the eligible devices

	Vector<VkPhysicalDevice> eligibleDevices;
	Vector<VkPhysicalDeviceProperties> deviceProperties;
	Vector<Vector<VkQueueFamilyProperties>> deviceQueueProperties;
	Vector<VkPhysicalDeviceMemoryProperties> deviceMemoryProperties;
	Vector<size_t> deviceVram;
	Vector<int> deviceScore;
	for(int i = 0; i < devCount; i++) {
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

	if(!eligibleDevices.getCount()) {
		log(STRINGIFY(engine::internals::vkLoad()), "No eligible GPUs found");
		exit(-1);
	}

	// Evaluate the devices

	// TODO: Optimize this code
	while(eligibleDevices.getCount() != 1) {
		// Vector for counting each device and what it has a higher score than
		Vector<int> deviceInferiorCount;
		countInferiors(deviceInferiorCount, deviceScore);

		// Set to true everytime something isn't removed
		bool repeat = true;

		for(int i = 0; i < deviceInferiorCount.getCount(); i++) {
			// Filter out everything that isn't better than something
			if(deviceInferiorCount[i] == 0) {
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
		if(repeat) {
			VkPhysicalDevice dev = eligibleDevices[0];

			for(int i = 0; i < deviceProperties.getCount(); i++) {
				if(deviceProperties[i].deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || deviceProperties[i].deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU) {
					dev = eligibleDevices[i];
					break;
				}
			}

			for(int i = 0; i < eligibleDevices.getCount(); i++) {
				if(eligibleDevices[i] != dev) {
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

	physicalDevice = eligibleDevices[0];
	physicalDeviceProperties = deviceProperties[0];
	physicalDeviceMemoryProperties = deviceMemoryProperties[0];
	physicalDeviceVRAM = deviceVram[0];

	// Log the choice

	log(STRINGIFY(vkLoad()), "Selected GPU: %s", deviceProperties[0].deviceName);

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

	if(vkNullCall(STRINGIFY(vkCreateDevice), physicalDevice, &devInfo, &device) != VK_SUCCESS) {
		log(STRINGIFY(vkLoad()), "Failure to create the logical device");
		exit(-1);
	}

	#ifdef CITRUS_ENGINE_WINDOWS

	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo;
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = NULL;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.hinstance = hinstance;
	surfaceCreateInfo.hwnd = hwnd;

	if(vkInstanceCall(STRINGIFY(vkCreateWin32SurfaceKHR), instance, &surfaceCreateInfo, NULL, &surface) != VK_SUCCESS) {
		log(STRINGIFY(vkLoad()), "Failure to create the swapchain surface");
		exit(-1);
	}

	#else

	VkXlibSurfaceCreateInfoKHR surfaceCreateInfo;
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.pNext = NULL;
	surfaceCreateInfo.flags = 0;
	surfaceCreateInfo.dpy = display;
	surfaceCreateInfo.window = window;

	if(vkInstanceCall(STRINGIFY(vkCreateXlibSurfaceKHR), instance, &surfaceCreateInfo, NULL, &surface) != VK_SUCCESS) {
		log(STRINGIFY(vkLoad()), "Failure to create the swapchain surface");
		exit(-1);
	}

	#endif

	vkCreateSwapChain(0, 0); // TODO: real values
}

void vkCreateSwapChain(int width, int height)
{
	VkSwapchainCreateInfoKHR swapInfo;
	swapInfo.sType = VkSwapchainCreateInfoKHR;
	swapInfo.pNext = NULL;
	swapInfo.flags = 0;
	swapInfo.surface = surface;
	swapInfo.minImageCount = 3; // Triple buffering
	swapInfo.imageFormat = VK_FORMAT_B8G8R8A8_SRGB; // TODO: Check for color support
	swapInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapInfo.imageExtent = { width, height } ;
	swapInfo.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT; // post-processing + bliting with UI
	swapInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapInfo.queueFamilyIndexCount = 0;
	swapInfo.pQueueFamilyIndices = NULL;
	swapInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	swapInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // TODO: option to change this
	swapInfo.presentMode = VK_PRESENT_MODE_MAILBOX_KHR; // TODO: Vsync + framerate detection
	swapInfo.clipped = VK_TRUE;
	swapInfo.oldSwapchain = swapchain;

	if(vkDeviceCall(STRINGIFY(vkCreateSwapchainKHR), device, &swapInfo, NULL, &swapchain) != VK_SUCCESS) {
		log(STRINGIFY(vkCreateSwapChain()), "Failure to create the swapchain");
		exit(-1);
	}
}