#pragma once 
#include <volk/volk.h>
#include <GLFW/glfw3.h>
#include <optional>
#include <vector>
#include <cstdint>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
 bool isComplete() const {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


struct VulkanContext {
public:
    VkInstance instance = VK_NULL_HANDLE;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice = VK_NULL_HANDLE;
	
  VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;
	VkSurfaceKHR surface = VK_NULL_HANDLE;

	QueueFamilyIndices queueFamilyIndices;

	VulkanContext() = default;
	~VulkanContext();
	VulkanContext(const VulkanContext&) = delete;
	VulkanContext& operator=(const VulkanContext&) = delete;

	void initialize(GLFWwindow* window);
	void cleanup();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
	SwapChainSupportDetails getSwapChainSupport(VkPhysicalDevice device) const;

private:
	void createInstance();
	void createSurface(GLFWwindow* window);
	void pickPhysicalDevice();
	void createLogicalDevice();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device) const;
	bool isDeviceSuitable(VkPhysicalDevice device) const;
	std::vector<const char*> getRequiredExtensions() const;

};
