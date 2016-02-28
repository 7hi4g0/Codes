#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "window.h"

#define APP_NAME	"Vulkan Test"
#define APP_VERSION	1

int main() {
	VkXcbSurfaceCreateInfoKHR surface_info = createWindow();
	
	VkApplicationInfo app_info = {};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = NULL;
	app_info.pApplicationName = APP_NAME;
	app_info.applicationVersion = APP_VERSION;
	app_info.pEngineName = APP_NAME;
	app_info.engineVersion = APP_VERSION;
	app_info.apiVersion = VK_API_VERSION;

	const char* extensions[2] = {"VK_KHR_surface", "VK_KHR_xcb_surface"};

	VkInstanceCreateInfo inst_info = {};
	inst_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	inst_info.pNext = NULL;
	inst_info.flags = 0;
	inst_info.pApplicationInfo = &app_info;
	inst_info.enabledLayerCount = 0;
	inst_info.ppEnabledLayerNames = NULL;
	inst_info.enabledExtensionCount = 2;
	inst_info.ppEnabledExtensionNames = extensions;

	VkInstance inst;
	VkResult res;

	res = vkCreateInstance(&inst_info, NULL, &inst);

	if (res != VK_SUCCESS) {
		printf("Error creating instance\nError number: %d", res);
		exit(-1);
	}
	printf("Instance created!\n");

	uint32_t dev_count;
	VkPhysicalDevice* devices;

	res = vkEnumeratePhysicalDevices(inst, &dev_count, NULL);
	if (res != VK_SUCCESS) {
		printf("Error querying physical device count\nError number: %d", res);
		exit(-1);
	}
	printf("Found %d physical devices\n", dev_count);

	devices = (VkPhysicalDevice *) malloc(sizeof(VkPhysicalDevice) * dev_count);
	vkEnumeratePhysicalDevices(inst, &dev_count, devices);
	if (res != VK_SUCCESS) {
		printf("Error querying physical device\nError number: %d", res);
		exit(-1);
	}
	printf("Got %d physical devices handles\n", dev_count);

	uint32_t queue_index;
	uint32_t queue_count;

	for (int dev_idx = 0; dev_idx < dev_count; dev_idx++) {
		VkPhysicalDeviceProperties dev_prop;

		vkGetPhysicalDeviceProperties(devices[dev_idx], &dev_prop);
		printf("%s\n", dev_prop.deviceName);

		uint32_t queue_family_count;
		VkQueueFamilyProperties* queue_families;

		vkGetPhysicalDeviceQueueFamilyProperties(devices[dev_idx], &queue_family_count, NULL);
		printf("Found %d queue families\n", queue_family_count);

		queue_families = (VkQueueFamilyProperties *) malloc(sizeof(VkQueueFamilyProperties) * queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(devices[dev_idx], &queue_family_count, queue_families);

		for (int queue_idx = 0; queue_idx < queue_family_count; queue_idx++){
			VkQueueFamilyProperties queue = queue_families[queue_idx];

			printf(
					"Flags: %x\n"
					"Count: %d\n"
					"Timestamp Bits: %d bits\n",
					queue.queueFlags, queue.queueCount, queue.timestampValidBits);

			if (queue.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				queue_index = queue_idx;
				queue_count = queue.queueCount;
			}
		}

		free(queue_families);
	}

	VkPhysicalDevice physical_device = devices[0];

	free(devices);

	VkBool32 test;

	test = vkGetPhysicalDeviceXcbPresentationSupportKHR(physical_device, queue_index, conn, screen->root_visual);
	if (!test) {
		printf("Physical Device not compatible with created Window! %d\n", test);
		exit(-1);
	}
	printf("Physical Device compatible with created Window\n");

	float queue_priorities[1] = {0.0};

	VkDeviceQueueCreateInfo queue_info = {};
	queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_info.pNext = NULL;
	queue_info.flags = 0;
	queue_info.queueFamilyIndex = queue_index;
	queue_info.queueCount = queue_count;
	queue_info.pQueuePriorities = queue_priorities;

	VkDeviceCreateInfo dev_info = {};
	dev_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dev_info.pNext = NULL;
	dev_info.flags = 0;
	dev_info.queueCreateInfoCount = 1;
	dev_info.pQueueCreateInfos = &queue_info;
	dev_info.enabledLayerCount = 0;
	dev_info.ppEnabledLayerNames = NULL;
	dev_info.enabledExtensionCount = 0;
	dev_info.ppEnabledExtensionNames = NULL;
	dev_info.pEnabledFeatures = NULL;

	VkDevice device;

	res = vkCreateDevice(physical_device, &dev_info, NULL, &device);
	if (res != VK_SUCCESS) {
		printf("Error connecting to device\nError number: %d\n", res);
		exit(-1);
	}
	printf("Connected to device\n");

	usleep(1000000);

	vkDestroyDevice(device, NULL);

	vkDestroyInstance(inst, NULL);

	destroyWindow();

	usleep(1000000);

	return 0;
}
