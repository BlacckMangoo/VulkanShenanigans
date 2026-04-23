#pragma once
#include <volk/volk.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>
#include "vulkanContext.h"
#include "window.h"

class Application {
public:
	Application() {
		initVulkan();
	};

	~Application() {
		cleanup();
	}

	void cleanup();
	void run();

	void drawFrame();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFrameBuffer();
	void createCommandPool();
	void createCommandBuffers();
	void createSyncObjects();

	VulkanContext ctx;
	std::vector<const char*> getRequiredExtensions();

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VkShaderModule createShaderModule(const std::vector<char>& code);
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
private:
	
	Window window{1080, (1080*4)/3};

	void initVulkan();

	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;
	VkSwapchainKHR m_swapChain;

	std::vector<VkImage> m_swapChainImages;
	std::vector<VkImageView> m_swapChainImageViews;
	std::vector<VkFramebuffer> m_swapChainFramebuffers;

	VkRenderPass m_renderPass;
	VkPipelineLayout m_pipelineLayout;
	VkPipeline m_graphicsPipeline;
	VkCommandPool m_commandPool;
	VkCommandBuffer m_commandBuffer;

	//Synchronisation 

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;
};