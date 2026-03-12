#pragma once 
#include <volk/volk.h>

namespace VkInit {

	inline VkApplicationInfo createAppInfo(const char* appName)
	{
		VkApplicationInfo appInfo{};

		// JUST META DETA FOR THE DRIVER MOSTLY 

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = appName;
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); 
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_3;
	    
		return appInfo;
	}

	inline VkInstanceCreateInfo instanceCreateInfo(const VkApplicationInfo* appInfo)
	{
		VkInstanceCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		info.pApplicationInfo = appInfo;
		return info;
	}

}