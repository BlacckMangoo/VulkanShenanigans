#pragma once 
#include <volk/volk.h>
#include <GLFW/glfw3.h>
#include <cstdint>

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


		void pickPhysicalDevice();
		void createLogicalDevice();



		

private:
	GLFWwindow* m_window;
	void initWindow();
	void initVulkan();
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	VkInstance m_instance;
	VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	VkDevice m_device;
	VkQueue m_graphicsQueue;


};