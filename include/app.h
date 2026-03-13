#pragma once 
#include <volk/volk.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() &&
			presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


class Application {
	public:
	
		Application() {
			initWindow();
			initVulkan();
		};
		~Application() {
			cleanup();
		}

		void cleanup();

		void run();


		int getHeight()
		{
			return HEIGHT;
		}

		int getWidth()
		{
			return WIDTH;
		}

		void createInstance();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void createImageViews();
		void createGraphicsPipeline();


		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		inline bool isDeviceSuitable(VkPhysicalDevice device);
		inline bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);



private:
	GLFWwindow* m_window;
	void initWindow();
	void initVulkan();
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	VkInstance m_instance;

	const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE; // physical device
	VkDevice m_device;  // logical device
	VkQueue m_graphicsQueue;
	VkQueue m_presentQueue;


	VkSurfaceKHR m_surface;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;
	VkSwapchainKHR m_swapChain;
	std::vector<VkImage> m_swapChainImages;

	std::vector<VkImageView> m_swapChainImageViews;


};