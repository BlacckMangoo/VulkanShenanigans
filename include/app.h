#pragma once
#include <volk/volk.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <vector>
#include "vulkanContext.h"
#include "window.h"
#include "glm/glm.hpp"
#include <array>

struct Vertex {

	glm::vec3 pos; 
	glm::vec3 color;
	
	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static std::array< VkVertexInputAttributeDescription,2> getAttributeDescription() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		
		return attributeDescriptions;
	}
};



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

	void createVertexBuffer();
	VkBuffer vertexBuffer{};
	VkDeviceMemory vertexBufferMemory{};

	
	std::vector<Vertex> vertices = {
   {{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
   {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
   {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
	};


	VulkanContext ctx;
	std::vector<const char*> getRequiredExtensions();

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VkShaderModule createShaderModule(const std::vector<char>& code);
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
	int currentFrame = 0;
	std::vector<VkCommandBuffer> m_commandBuffers;

	//Synchronisation 

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

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

	
};