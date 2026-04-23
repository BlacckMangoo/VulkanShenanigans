#pragma once 
#include <GLFW/glfw3.h>

struct Window {


	Window( int height , int width ) : height(height), width(width) {
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

	}

	~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	GLFWwindow* get() const { return window; }
	int getHeight() const { return height; }
	int getWidth() const { return width; }

private:
    GLFWwindow* window; 
	int height{500}; 
	int width{800};

};